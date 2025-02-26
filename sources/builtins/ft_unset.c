/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:33:13 by mleproux          #+#    #+#             */
/*   Updated: 2025/02/25 16:48:26 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	search_and_unset(t_env_var *env_var, char *name, t_env_var *tmp)
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
}

void	ft_unset(t_data *data, t_command *cmd)
{
	int			i;
	char		*name;
	t_env_var	*tmp;
	t_env_var	*env_var;

	i = 0;
	while (cmd->args[++i] != NULL)
	{
		name = get_env_var_name(cmd->args[i]);
		if (name == NULL)
			return ;
		if (exist_var(data, name) == 0)
			return (free(name));
		env_var = data->env_variables;
		if (env_var == NULL)
			return ;
		if (ft_strncmp(env_var->name, name, ft_strlen(name)) == 0
			&& ft_strlen(env_var->name) == ft_strlen(name))
		{
			tmp = env_var;
			env_var = env_var->next;
			free_env_var(tmp);
		}
		else
			search_and_unset(env_var, name, tmp);
		free(name);
	}
}
