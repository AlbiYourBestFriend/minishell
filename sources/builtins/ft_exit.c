/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:33:53 by mleproux          #+#    #+#             */
/*   Updated: 2025/03/17 18:00:27 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exit(t_data *data, t_command *cmd, int p)
{
	if (p == 1 && cmdsize(data->commands) == 1)
	{
		printf("exit\n");
		if (tab_len(cmd->args) > 1)
		{
			if (ft_is_atoi(cmd->args[1]) == 0)
			{
				printf("%sexit: %s: numeric argument required\n", \
						ERROR, cmd->args[1]);
				ft_free_all_exit(data, 2);
			}
			else if (tab_len(cmd->args) > 2)
			{
				printf("%sexit: too many arguments\n", ERROR);
				g_exit_status = 1;
				return ;
			}
			ft_free_all_exit(data, ft_atoi(cmd->args[1]));
		}
	}
	ft_free_all_exit(data, 0);
}

// nombre doit etre un long
// le nombre modulo 256 donne le exit code
