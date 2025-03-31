/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:33:53 by mleproux          #+#    #+#             */
/*   Updated: 2025/03/31 16:27:02 by mleproux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exit(t_data *data, t_command *cmd)
{
	ft_printf("exit\n");
	if (tab_len(cmd->args) > 1)
	{
		if (ft_is_atol(cmd->args[1]) == 0)
		{
			ft_printf("%sexit: %s: numeric argument required\n", \
					ERROR, cmd->args[1]);
			free_all_exit(data, 2);
		}
		else if (tab_len(cmd->args) > 2)
		{
			ft_printf("%sexit: too many arguments\n", ERROR);
			g_exit_status = 1;
			return ;
		}
		free_all_exit(data, ft_atol(cmd->args[1]) % 256);
	}
	free_all_exit(data, 0);
}

// nombre doit etre un long
// le nombre modulo 256 donne le exit code
