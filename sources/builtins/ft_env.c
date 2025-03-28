/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:33:34 by mleproux          #+#    #+#             */
/*   Updated: 2025/03/28 11:51:03 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_env(t_data *data, t_command *cmd)
{
	t_env_var	*env_var;

	env_var = data->env_variables;
	if (tab_len(cmd->args) > 1)
	{
		ft_printf("env: ‘%s‘: %s\n", cmd->args[1], NO_FILE_DIR);
		g_exit_status = 127;
		return ;
	}
	while (env_var != NULL)
	{
		if (env_var->status == 1)
		{
			ft_putstr_fd(env_var->name, 1);
			ft_putstr_fd("=", 1);
			if (env_var->value != NULL)
				ft_putstr_fd(env_var->value, 1);
			ft_putstr_fd("\n", 1);
		}
		env_var = env_var->next;
	}
	g_exit_status = 0;
}
