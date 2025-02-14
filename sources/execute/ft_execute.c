/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 14:59:12 by mleproux          #+#    #+#             */
/*   Updated: 2025/02/13 19:09:24 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	try_execute(char *path, t_env_var *env_var, char **cmds)
{
	char	**tab;

	if (access(path, F_OK | X_OK) == 0)
	{
		tab = lst_to_tab(env_var);
		execve(path, cmds, tab);
		free(path);
		free_tab(tab);
		printf("erreur");
	}
}

static void	command_executor(t_data *data, t_command *cmd)
{
	char	**paths;
	char	*path;
	int		index;

	index = 0;
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
}

void	fork_handler(t_data *data, t_command *cmd, int input, int output)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		print_error("Fork failed");
	else if (pid == 0)
	{
		if (dup2(input, 0) == -1 || dup2(output, 1) == -1)
			print_error("Dup failed");
		if (check_if_builtins(cmd) == 1) // a mettre en dehors du fork !
			execute_builtins(data, cmd); // le fork sert uniquement pour le execve
		else
			command_executor(data, cmd);
	}
	else
	{
		if (input != 0)
			close(input);
		wait(NULL);
	}
}

void	ft_execute(t_data *data)
{
	t_command	*temp;
	int			input;
	int			pipefd[2];	

	if (pipe(pipefd) != 0) // <-- pipe
		return ;
	temp = data->commands;
	input = temp->input_fd;
	write(1, "4", 1);
	while (temp->next)
	{
		write(1, "8", 1);
		if (pipe(pipefd) != 0) // <-- autre pipe ?  =>  2 a la suite ???
			return ;
		write(1, "9", 1);
		fork_handler(data, temp, input, pipefd[1]);
		close(pipefd[1]);
		input = pipefd[0];
		temp = temp->next;
		write(1, "5", 1);
	}
	write(1, "6", 1);
	fork_handler(data, temp, input, temp->output_fd);
	write(1, "7", 1);
	close(input);
}
