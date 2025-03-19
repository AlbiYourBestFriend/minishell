/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 14:59:12 by mleproux          #+#    #+#             */
/*   Updated: 2025/03/19 12:31:22 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	try_execute(char *path, t_env_var *env_var, char **cmds, int n)
{
	char	**tab;

	if (!path)
		return (0);
	if (access(path, F_OK) == 0)
	{
		if (access(path, X_OK) == -1)
		{
			g_exit_status = 126;
			if (path != NULL && n)
				free(path);
			return (nofile_error(NO_PERM, cmds[0]), 0);
		}
		tab = lst_to_tab(env_var);
		if (tab == NULL)
			return (0);
		execve(path, cmds, tab);
		printf("%s%s: command not found\n", ERROR, cmds[0]);
		g_exit_status = 127;
		free_tab(tab);
		if (path != NULL && n)
			free(path);
		return (0);
	}
	return (1);
}

static void	command_executor(t_data *data, t_command *cmd)
{
	char	**paths;
	char	*path;
	int		index;

	index = 0;
	if (cmd->args[0][0] == '/'
		&& try_execute(cmd->args[0], data->env_variables, cmd->args, 0) == 0)
		free_all_exit(data, g_exit_status);
	paths = ft_split(get_env_var(data, "PATH")->value, ':');
	if (paths == NULL)
		return (allocate_error(ALLOC_ERR));
	while (paths[index] != NULL)
	{
		path = create_path(paths[index], cmd->args[0]);
		if (path == NULL)
			return (free_tab(paths), allocate_error(ALLOC_ERR));
		if (try_execute(path, data->env_variables, cmd->args, 1) == 0)
			return (free_tab(paths), free_all_exit(data, g_exit_status));
		free(path);
		index++;
	}
	free_tab(paths);
	printf("%s%s: command not found\n", ERROR, cmd->args[0]);
	g_exit_status = 127;
}

void	fork_handler(t_data *data, t_command *cmd, int *pipefd)
{
	cmd->pid = fork();
	if (cmd->pid == -1)
		printf("%s%s\n", ERROR, FORK_ERR);
	else if (cmd->pid == 0)
	{
		if (cmd->args == NULL && process_cmd_line(data, cmd) == 0)
			return (free_all_exit(data, g_exit_status));
		if (cmd->next != NULL)
		{
			fd_handler(cmd, pipefd[1], pipefd[0]);
			close(pipefd[0]);
			close(pipefd[1]);
		}
		close(cmd->input_fd);
		close(cmd->output_fd);
		if (cmd->input_fd != 0 && dup2(cmd->input_fd, 0) == -1)
			free_all_exit(data, 1);
		if (cmd->output_fd != 1 && dup2(cmd->output_fd, 1) == -1)
			free_all_exit(data, 1);
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
	while (temp->next != NULL)
	{
		if (pipe(pipefd) != 0)
			return (printf("%s%s\n", ERROR, PIPE_ERR), 0);
		fork_handler(data, temp, pipefd);
		if (temp->next != NULL)
		{
			close(pipefd[1]);
			if (temp->input_fd != 0)
				close(temp->input_fd);
			temp->next->input_fd = pipefd[0];
		}
		temp = temp->next;
	}
	fork_handler(data, temp, pipefd);
	return (wait_for_all(data), 1);
}
