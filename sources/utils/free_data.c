/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:20:59 by tprovost          #+#    #+#             */
/*   Updated: 2025/02/17 15:14:21 by mleproux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_data(t_data *data)
{
	t_env_var	*var;

	free_cmds(data);
	var = data->env_variables;
	while (data->env_variables != NULL)
	{
		var = data->env_variables->next;
		free_env_var(data->env_variables);
		data->env_variables = var;
	}
}
