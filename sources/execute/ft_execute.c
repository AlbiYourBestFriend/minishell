/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 14:59:12 by mleproux          #+#    #+#             */
/*   Updated: 2025/02/20 14:26:03 by mleproux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	try_execute(char *path, t_env_var *env_var, char **cmds)
{
	char	**tab;

	if (access(path, F_OK | X_OK) == 0)
	{
		tab = lst_to_tab(env_var);
		execve(path, cmds, tab);
		free_tab(tab);
		perror("erreur");
		// free data
		// exit
	}
}

// il faut gerer le execution de file : ./a.out ...
static void	command_executor(t_data *data, t_command *cmd)
{
	char	**paths;
	char	*path;
	int		index;

	index = 0;
	try_execute(cmd->args[0], data->env_variables, cmd->args);
	paths = get_paths();
	if (paths == NULL)
		printf("Erreur");
	while (paths[index] != NULL)
	{
		path = create_path(paths[index], cmd->args[0]);
		if (!path)
			printf("Erreur");
		try_execute(path, data->env_variables, cmd->args);
		free(path);
		index++;
	}
	free_tab(paths);
	perror("command not found");
}

void fd_handler(t_command *cmd, int output, int input)
{
    if (cmd->output_fd == 1 && output != -2)
    {
        cmd->output_fd = output;
        if (cmd->next && cmd->next->input_fd == 0)
            cmd->next->input_fd = input;
    }
    else if (cmd->output_fd != 1 && cmd->next == NULL)
        cmd->output_fd = output;
}
void	fork_handler(t_data *data, t_command *cmd, int *pipefd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		perror("Fork failed");
	else if (pid == 0)
	{
		if (cmd->args == NULL)
			read_redirection(cmd);
		if (cmd->next)
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
			exec_executable(data->env_variables, cmd);
		else
			command_executor(data, cmd);
		ft_exit(data, cmd);
	}
	else
	{
		if (cmd->input_fd != 0)
			close(cmd->input_fd);
	}
}

void ft_execute(t_data *data)
{
    t_command *temp;
    int pipefd[2];

    temp = data->commands;
    if (cmdsize(data->commands) == 1)
    {
        if (init_builtins(data, temp) == 1)
			return ;
    }
    while (temp)
    {
        if (pipe(pipefd) != 0)
        {
            perror("pipe");
            return;
        }
        fork_handler(data, temp, pipefd);
		if (temp->next)
        {
            close(pipefd[1]);
            if (temp->input_fd != 0)
                close(temp->input_fd);
            temp = temp->next;
            temp->input_fd = pipefd[0];
        }
		else	
			temp= temp->next;
    }
}
