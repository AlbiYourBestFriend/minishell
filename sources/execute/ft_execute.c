/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 14:59:12 by mleproux          #+#    #+#             */
/*   Updated: 2025/02/25 11:53:13 by mleproux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	try_execute(char *path, t_env_var *env_var, char **cmds, t_data *data)
{
	char	**tab;
	
	if (access(path, F_OK | X_OK) == 0)
	{
		tab = lst_to_tab(env_var);
		execve(path, cmds, tab);
		free_tab(tab);
		perror("Execve failed");
		free_data(data);
		if (path)
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
	if (try_execute(cmd->args[0], data->env_variables, cmd->args, data) == 0)
		exit(1);
	paths = ft_split(getenv("PATH"), ':');
	if (paths == NULL)
		perror("Erreur");
	while (paths[index] != NULL)
	{
		path = create_path(paths[index], cmd->args[0]);
		if (!path)
			perror("Erreur");
		if (try_execute(path, data->env_variables, cmd->args, data) == 0)
		{
			free_tab(paths);
			exit(1);
		}
		free(path);
		index++;
	}
	free_tab(paths);
	perror("command not found");
}

void	fd_handler(t_command *cmd, int output, int input)
{
	if (cmd->output_fd == 1 && cmd->output_fd != output)
	{
		cmd->output_fd = output;
		if (cmd->next && cmd->next->input_fd == 0)
			cmd->next->input_fd = input;
	}
	else if (cmd->output_fd != 1 && cmd->next == NULL)
		cmd->output_fd = output;
}

void	wait_for_all(t_data *data)
{
	t_command	*temp;

	temp = data->commands;
	while (temp != NULL)
	{
		waitpid(temp->pid, NULL, 0);
		temp = temp->next;
	}
}

void	fork_handler(t_data *data, t_command *cmd, int *pipefd)
{
	cmd->pid = fork();
	if (cmd->pid == -1)
		perror("Fork failed");
	else if (cmd->pid == 0)
	{
		if (cmd->args == NULL)
			read_redirection(data, cmd);
		if (cmd->next != NULL)
			fd_handler(cmd, pipefd[1], pipefd[0]);
		else
			fd_handler(cmd, cmd->output_fd, -2);
		if (cmd->input_fd != 0)
			dup2(cmd->input_fd, 0);
		if (cmd->output_fd != 1)
			dup2(cmd->output_fd, 1);
		if (check_if_builtins(cmd))
			execute_builtins(data, cmd);
		else if (is_executable(cmd->args[0]) == 1)
			exec_executable(data, cmd);
		else
			command_executor(data, cmd);
		ft_exit(data, cmd, 0);
	}
	else
	{
		if (cmd->input_fd != 0)
			close(cmd->input_fd);
	}
}

void	ft_execute(t_data *data)
{
	int			pipefd[2];
	t_command	*temp;

	temp = data->commands;
	if (cmdsize(data->commands) == 1)
	{
		if (init_builtins(data, temp) == 1)
			return ;
	}
	while (temp != NULL)
	{
		if (pipe(pipefd) != 0)
		{
			perror("pipe");
			return ;
		}
		fork_handler(data, temp, pipefd);
		if (temp->next != NULL)
		{
			close(pipefd[1]);
			if (temp->input_fd != 0)
				close(temp->input_fd);
			temp = temp->next;
			temp->input_fd = pipefd[0];
		}
		else
			temp = temp->next;
	}
	wait_for_all(data);
}
