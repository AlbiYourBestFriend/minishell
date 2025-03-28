/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:12:13 by mleproux          #+#    #+#             */
/*   Updated: 2025/03/27 16:20:00 by mleproux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_close(t_command *cmd, int x)
{
	if (x == 1 && cmd->input_fd != -1)
	{
		close(cmd->input_fd);
		cmd->input_fd = -1;
	}
	else if (x == 2 && cmd->output_fd != -1)
	{
		close(cmd->output_fd);
		cmd->output_fd = -1;
	}
	else if (x == 3 && cmd->heredoc_fd != -1)
	{
		close(cmd->heredoc_fd);
		cmd->heredoc_fd = -1;
	}
}
