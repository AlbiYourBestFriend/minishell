/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:13:48 by mleproux          #+#    #+#             */
/*   Updated: 2025/03/27 15:08:25 by tprovost         ###   ########.fr       */
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
		return (allocate_error(ALLOC_ERR), NULL);
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
	while (str[i] != '=' && str[i] != '\0')
		i++;
	if (str[i] == '=')
		i++;
	if (str[i] != '\0')
	{
		value = ft_strdup(&str[i]);
		if (value == NULL)
			return (allocate_error(ALLOC_ERR), NULL);
	}
	return (value);
}

static t_env_var	*new_env_var(char *env_i)
{
	t_env_var	*new_var;

	if (is_env_var(env_i) == -2)
		return (NULL);
	new_var = malloc(sizeof(t_env_var));
	if (new_var == NULL)
		return (allocate_error(ALLOC_ERR), NULL);
	new_var->name = get_env_name(env_i);
	if (new_var->name == NULL)
		return (free(new_var), NULL);
	new_var->value = get_env_value(env_i);
	if (new_var->value == NULL && is_env_var(env_i) == 1)
		return (free(new_var->name), free(new_var), NULL);
	new_var->status = 1;
	new_var->next = NULL;
	return (new_var);
}

static int	put_env_to_data(t_data *data, char **env)
{
	int			i;
	t_env_var	*tmp_env_var;

	tmp_env_var = new_env_var(env[0]);
	if (tmp_env_var == NULL)
		return (0);
	data->env_variables = tmp_env_var;
	i = 1;
	while (env[i] != NULL)
	{
		tmp_env_var->next = new_env_var(env[i]);
		if (tmp_env_var->next == NULL && is_env_var(env[i]) != -2)
			return (0);
		if (is_env_var(env[i]) != -2)
			tmp_env_var = tmp_env_var->next;
		i++;
	}
	return (1);
}

t_data	init_data(char **env, char *filelocation)
{
	t_data	data;

	data.env_variables = NULL;
	data.commands = NULL;
	data.splitted_cmds = NULL;
	data.program_path = NULL;
	data.tmp_path = NULL;
	data.count_line = 0;
	data.exit_status = 0;
	if (env != NULL && env[0] != NULL && put_env_to_data(&data, env) == 0)
	{
		free_data(&data);
		exit(1);
	}
	get_program_path(&data, filelocation);
	return (data);
}
