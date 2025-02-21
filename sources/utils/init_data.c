/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:13:48 by mleproux          #+#    #+#             */
/*   Updated: 2025/02/21 12:55:55 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_env_name(char *str)
{
	int		i;
	char	*name;

	i = 0;
	while (str[i] != '=')
		i++;
	name = malloc((i + 1) * sizeof(char));
	if (name == NULL)
		return (NULL);
	i = 0;
	while (str[i] != '=')
	{
		name[i] = str[i];
		i++;
	}
	name[i] = '\0';
	return (name);
}

static char	*get_env_value(char *str)
{
	int		i;
	char	*value;

	i = 0;
	value = NULL;
	while (str[i] != '=')
		i++;
	i++;
	if (str[i] != '\0')
		value = ft_strdup(&str[i]);
	return (value);
}

static t_env_var	*new_env_var(char *env_i)
{
	t_env_var	*new_var;

	new_var = malloc(sizeof(t_env_var));
	if (new_var == NULL)
		return (NULL);
	new_var->name = get_env_name(env_i);
	new_var->value = get_env_value(env_i);
	new_var->status = 1;
	new_var->next = NULL;
	return (new_var);
}

static void	put_env_to_data(t_data *data, char **env)
{
	t_env_var	*new_var;
	t_env_var	*last_var;
	int			i;

	new_var = new_env_var(env[0]);
	data->env_variables = new_var;
	last_var = new_var;
	i = 1;
	while (env[i] != NULL)
	{
		new_var = new_env_var(env[i]);
		last_var->next = new_var;
		last_var = last_var->next;
		i++;
	}
}

t_data	init_data(char **env)
{
	t_data	data;

	data.commands = NULL;
	data.splitted_cmds = NULL;
	data.count_line = 0;
	put_env_to_data(&data, env);
	return (data);
}
