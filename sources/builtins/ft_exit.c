/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:33:53 by mleproux          #+#    #+#             */
/*   Updated: 2025/02/27 17:32:39 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exit(t_data *data, t_command *cmd, int p)
{
	if (p == 1 && cmdsize(data->commands) == 1)
	{
		if (tab_len(cmd->args) > 1)
		{
			if (ft_is_atoi(cmd->args[1]) == 0)
			{
				printf("exit\n");
				printf("%sexit: %s: numeric argument required\n", \
						ERREUR, cmd->args[1]);
			}
			else if (tab_len(cmd->args) > 2)
			{
				printf("%sexit: too many arguments\n", ERREUR);
				return ;
			}
		}
		else
			printf("exit\n");
	}
	ft_free_all_exit(data, g_exit_status);
}
