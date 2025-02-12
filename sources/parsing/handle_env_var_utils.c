/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env_var_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:20:14 by tprovost          #+#    #+#             */
/*   Updated: 2025/02/12 19:27:06 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exist_var(t_data *data, char *name)
{
	t_env_var	*env_var;

	env_var = data->env_variables;
	while (env_var != NULL
		&& ft_strncmp(env_var->name, name, ft_strlen(name)) != 0
		&& ft_strlen(env_var->name) != ft_strlen(name))
		env_var = env_var->next;
	if (env_var != NULL)
		return (1);
	return (0);
}

t_env_var	*add_env_var(t_data *data, char *name, char *value)
{
	t_env_var	*new_env_var;
	t_env_var	*tmp_env_var;

	new_env_var = malloc(sizeof(t_env_var));
	new_env_var->name = name;
	new_env_var->value = value;
	new_env_var->status = 0;
	new_env_var->next = NULL;
	tmp_env_var = data->env_variables;
	if (tmp_env_var == NULL)
		data->env_variables = new_env_var;
	else
	{
		while (tmp_env_var->next != NULL)
			tmp_env_var = tmp_env_var->next;
		tmp_env_var->next = new_env_var;
	}
	return (new_env_var);
}

t_env_var	*get_env_var(t_data *data, char *name)
{
	t_env_var	*env_var;

	env_var = data->env_variables;
	while (ft_strncmp(env_var->name, name, ft_strlen(name)) != 0
		&& ft_strlen(env_var->name) != ft_strlen(name)
		&& env_var != NULL)
		env_var = env_var->next;
	return (env_var);
}

int	skip_quote(char *cmd, int n, int s)
{
	char	c;

	c = cmd[n];
	n = n + s;
	while (cmd[n] != c)
		n = n + s;
	return (n);
}
