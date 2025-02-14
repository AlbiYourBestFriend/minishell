/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:20:59 by tprovost          #+#    #+#             */
/*   Updated: 2025/02/13 18:41:47 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_data(t_data *data)
{
	t_command	*tmp;
	t_env_var	*var;
	int i = 0;

	tmp = data->commands;
	while (data->commands != NULL)
	{
		tmp = data->commands->next;
		free_cmd(data->commands);
		data->commands = tmp;
	}
	var = data->env_variables;
	while (data->env_variables != NULL)
	{
		printf("%d : %s=%s\n", i,  data->env_variables->name, data->env_variables->value);
		var = data->env_variables->next;
		free_env_var(data->env_variables);
		data->env_variables = var;
		i++;
	}
}
