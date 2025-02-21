/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:20:59 by tprovost          #+#    #+#             */
/*   Updated: 2025/02/21 12:27:40 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_data(t_data *data)
{
	t_env_var	*var;

	if (data == NULL)
		return ;
	free_cmds(data);
	free_tab(data->splitted_cmds);
	var = data->env_variables;
	while (data->env_variables != NULL)
	{
		var = data->env_variables->next;
		free_env_var(data->env_variables);
		data->env_variables = var;
	}
}
