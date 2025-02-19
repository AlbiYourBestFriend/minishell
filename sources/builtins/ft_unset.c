/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:33:13 by mleproux          #+#    #+#             */
/*   Updated: 2025/02/19 18:08:42 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_unset(t_data *data, t_command *cmd)
{
	char		*name;
	t_env_var	*env_var;
	t_env_var	*tmp;

	name = get_env_var_name(cmd->args[1]);
	tmp = NULL;
	if (data->env_variables == NULL || name == NULL)
		return ;
	if (exist_var(data, name) == 0)
		return (free(name));
	env_var = data->env_variables;
	if (ft_strncmp(env_var->name, name, ft_strlen(name)) == 0
		&& ft_strlen(env_var->name) == ft_strlen(name))
	{
		tmp = env_var;
		env_var = env_var->next;
		free_env_var(tmp);
		free(name);
	}
	else
	{
		while (env_var->next != NULL
			&& (ft_strncmp(env_var->next->name, name, ft_strlen(name)) != 0
				|| ft_strlen(env_var->next->name) != ft_strlen(name)))
			env_var = env_var->next;
		if (env_var->next != NULL)
		{
			tmp = env_var->next;
			env_var->next = env_var->next->next;
			free_env_var(tmp);
		}
		free(name);
	}
}
