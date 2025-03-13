/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:55:36 by tprovost          #+#    #+#             */
/*   Updated: 2025/03/13 11:39:13 by mleproux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	int			status;

	status = 0;
	temp = data->commands;
	while (temp != NULL)
	{
		waitpid(temp->pid, &status, 0);
		g_exit_status = WEXITSTATUS(status);
		temp = temp->next;
	}
}
