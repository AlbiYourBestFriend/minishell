/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:33:13 by mleproux          #+#    #+#             */
/*   Updated: 2025/02/12 16:57:15 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	free_elem(t_env_var *env_var, t_env_var *tmp)
{
	tmp = env_var->next;
	free_env_var(env_var);
	env_var = tmp;
}

void	ft_unset(t_data *data, t_command *cmd)
{
	t_env_var	*env_var;
	t_env_var	*tmp;
	char		*name;

	// printf("Bonjour je suis la commande unset! (:");
	name = get_env_var_name(cmd->args[1]);
	if (data->env_variables == NULL || exist_var(data, name) == 0)
		return ;
	if (ft_strncmp(data->env_variables->name, name, ft_strlen(name)) == 0
		&& ft_strlen(data->env_variables->name) == ft_strlen(name))
		free_elem(data->env_variables, env_var);
	else
	{
		env_var = data->env_variables;
		while (env_var->next != NULL
			&& (ft_strncmp(env_var->next->name, name, ft_strlen(name)) != 0
			|| ft_strlen(env_var->next->name) != ft_strlen(name)))
			env_var = env_var->next;
		if (env_var->next != NULL)
			free_elem(env_var->next, tmp);
	}
}
