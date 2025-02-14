/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:33:34 by mleproux          #+#    #+#             */
/*   Updated: 2025/02/14 16:53:14 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_env(t_data *data, t_command *cmd)
{
	t_env_var	*env_var;
	int			fd_out;

	env_var = data->env_variables;
	fd_out = cmd->output_fd;
	while (env_var != NULL)
	{
		if (env_var->status == 1)
		{
			write(fd_out, env_var->name, ft_strlen(env_var->name));
			write(fd_out, "=", 1);
			if (env_var->value != NULL)
				write(fd_out, env_var->value, ft_strlen(env_var->value));
			write(fd_out, "\n", 1);
		}
		env_var = env_var->next;
	}
	// ft_exit(data, NULL);
}
