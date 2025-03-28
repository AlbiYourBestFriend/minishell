/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 14:59:12 by mleproux          #+#    #+#             */
/*   Updated: 2025/03/28 11:51:03 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	try_execute(char *path, t_env_var *env_var, char **cmds)
{
	char	**tab;

	if (!path)
		return (0);
	if (access(path, F_OK) == 0)
	{
		if (access(path, X_OK) == -1)
		{
			g_exit_status = 126;
			return (nofile_error(NO_PERM, cmds[0]), 0);
		}
		tab = lst_to_tab(env_var);
		if (tab == NULL)
			return (0);
		execve(path, cmds, tab);
		ft_printf("%s%s: command not found\n", ERROR, cmds[0]);
		g_exit_status = 127;
		free_tab(tab);
		return (0);
	}
	return (1);
}

static void	command_executor(t_data *data, t_command *cmd)
{
	int			index;
	char		*path;
	char		**paths;
	char		*env_path;

	index = 0;
	env_path = command_executor_utils(data, cmd);
	paths = ft_split(env_path, ':');
	if (paths == NULL)
		return (allocate_error(ALLOC_ERR));
	while (paths[index] != NULL)
	{
		path = create_path(paths[index], cmd->args[0]);
		if (path == NULL)
			return (free_tab(paths), allocate_error(ALLOC_ERR));
		if (try_execute(path, data->env_variables, cmd->args) == 0)
			return (free(path), free_tab(paths), \
				free_all_exit(data, g_exit_status));
		free(path);
		index++;
	}
	free_tab(paths);
	ft_printf("%s%s: command not found\n", ERROR, cmd->args[0]);
	g_exit_status = 127;
}

static void	close_fd(t_data *data, t_command *cmd, int *pipefd)
{
	t_command	*temp;

	if (pipefd)
	{
		close(pipefd[0]);
		close(pipefd[1]);
	}
	if (cmd->input_fd != 0)
		ft_close(cmd, 1);
	if (cmd->output_fd != 1)
		ft_close(cmd, 2);
	if (!data)
		return ;
	temp = data->commands;
	while (temp)
	{
		if (temp->heredoc_fd > 0)
			ft_close(temp, 3);
		temp = temp->next;
	}
}

void	fork_handler(t_data *data, t_command *cmd, int *pipefd)
{
	cmd->pid = fork();
	if (cmd->pid == -1)
		printf("%s%s\n", ERROR, FORK_ERR);
	else if (cmd->pid == 0)
	{
		if (cmd->args == NULL && process_cmd_line(data, cmd) == 0)
			return (close_fd(data, cmd, pipefd), \
			free_all_exit(data, g_exit_status));
		if (cmd->next != NULL)
			fd_handler(cmd, pipefd[1], pipefd[0]);
		if (cmd->input_fd != 0 && dup2(cmd->input_fd, 0) == -1)
			return (close_fd(data, cmd, pipefd), \
			free_all_exit(data, g_exit_status));
		if (cmd->output_fd != 1 && dup2(cmd->output_fd, 1) == -1)
			return (close_fd(data, cmd, pipefd), \
			free_all_exit(data, g_exit_status));
		close_fd(data, cmd, pipefd);
		if (check_if_builtins(cmd) == 1)
			execute_builtins(data, cmd);
		else if (is_executable(cmd->args[0]) == 1)
			exec_executable(data, cmd);
		else
			command_executor(data, cmd);
		free_all_exit(data, g_exit_status);
	}
}

int	ft_execute(t_data *data)
{
	int			pipefd[2];
	t_command	*temp;

	temp = data->commands;
	signal_handler(1);
	if (read_heredoc(data) == 0)
		return (0);
	if (cmdsize(data->commands) == 1 && init_builtins(data, temp) == 1)
		return (1);
	while (temp != NULL)
	{
		if (pipe(pipefd) != 0)
			return (ft_printf("%s%s\n", ERROR, PIPE_ERR), 0);
		fork_handler(data, temp, pipefd);
		close(pipefd[1]);
		if (temp->input_fd != 0)
			ft_close(temp, 1);
		if (temp->next != NULL)
			temp->next->input_fd = pipefd[0];
		else
			break ;
		temp = temp->next;
	}
	close_fd(NULL, temp, NULL);
	return (close(pipefd[0]), wait_for_all(data), 1);
}
