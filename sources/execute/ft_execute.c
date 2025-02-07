/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 14:59:12 by mleproux          #+#    #+#             */
/*   Updated: 2025/02/07 16:58:14 by mleproux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	fork_handler(t_data data, char **cmd, int input, int output)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		print_error("Fork failed");
	else if (pid == 0)
	{
		if (dup2(input, 0) == -1 || dup2(output, 1) == -1)
			print_error("Dup failed");
		command_executor(data.env, cmd);
	}
	else
	{
		if (input != 0)
			close(input);
		wait(NULL);
	}
}

void	ft_execute(t_data data, char **cmds)
{
	int		pipefd[2];	
	int		index;
	pid_t	fork;

	if (pipe(pipefd) != 0)
		return ;
	while(cmds[index])
	{
		if (check_if_builtins(NULL) == 1)
			execute_builtins(NULL);
		else
			fork_handler(data, NULL, 0, 0);
		index++;
	}	
}
