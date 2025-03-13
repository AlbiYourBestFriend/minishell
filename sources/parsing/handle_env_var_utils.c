/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env_var_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:20:14 by tprovost          #+#    #+#             */
/*   Updated: 2025/03/13 13:49:49 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exist_var(t_data *data, char *name)
{
	t_env_var	*env_var;

	env_var = data->env_variables;
	if (name == NULL)
		return (0);
	while (env_var != NULL
		&& (ft_strncmp(env_var->name, name, ft_strlen(name)) != 0
			|| ft_strlen(env_var->name) != ft_strlen(name)))
		env_var = env_var->next;
	if (env_var != NULL)
		return (1);
	return (0);
}

static	t_env_var	*new_env_var(char *name, char *value, int status)
{
	t_env_var	*new_env_var;

	new_env_var = malloc(sizeof(t_env_var));
	if (new_env_var == NULL)
		return (allocate_error(data, ALLOC_ERR), NULL);
	new_env_var->name = name;
	new_env_var->value = value;
	new_env_var->status = status;
	new_env_var->next = NULL;
	return (new_env_var);
}

t_env_var	*add_env_var(t_data *data, char *name, char *value)
{
	t_env_var	*new_var;
	t_env_var	*tmp_env_var;
	char		*tmp_value;

	tmp_value = NULL;
	if (name == NULL)
		return (NULL);
	if (value != NULL)
	{
		tmp_value = ft_strdup(value);
		if (tmp_value == NULL)
			return (allocate_error(data, ALLOC_ERR), NULL);
	}
	new_var = new_env_var(name, tmp_value, 0);
	if (data->env_variables == NULL)
		data->env_variables = new_var;
	else
	{
		tmp_env_var = data->env_variables;
		while (tmp_env_var->next != NULL)
			tmp_env_var = tmp_env_var->next;
		tmp_env_var->next = new_var;
	}
	return (new_var);
}

t_env_var	*get_env_var(t_data *data, char *name)
{
	t_env_var	*env_var;

	env_var = data->env_variables;
	if (name == NULL)
		return (NULL);
	while (env_var != NULL
		&& (ft_strncmp(env_var->name, name, ft_strlen(name)) != 0
			|| ft_strlen(env_var->name) != ft_strlen(name)))
		env_var = env_var->next;
	return (env_var);
}

int	skip_quote(char *cmd, int n, int s)
{
	char	c;

	c = cmd[n];
	if (s != 1 && s != -1)
		return (-1);
	n = n + s;
	while (cmd[n] != c && cmd[n] != '\0' && n != 0)
		n = n + s;
	return (n);
}
