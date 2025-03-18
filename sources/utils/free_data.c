/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:20:59 by tprovost          #+#    #+#             */
/*   Updated: 2025/03/18 14:42:14 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_data(t_data *data)
{
	t_env_var	*var;

	if (data == NULL)
		return ;
	free_cmds(data);
	var = data->env_variables;
	while (data->env_variables != NULL)
	{
		var = data->env_variables->next;
		free_env_var(data->env_variables);
		data->env_variables = var;
	}
	if (data->splitted_cmds != NULL)
		free_tab(data->splitted_cmds);
	if (data->program_path != NULL)
		free(data->program_path);
	if (data->tmp_path != NULL)
		free(data->tmp_path);
	if (data->username != NULL)
		free(data->username);
	data = NULL;
}
