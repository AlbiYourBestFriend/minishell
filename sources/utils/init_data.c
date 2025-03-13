/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:13:48 by mleproux          #+#    #+#             */
/*   Updated: 2025/03/13 19:20:12 by tprovost         ###   ########.fr       */
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
	while (str[i] != '=')
		i++;
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

	new_var = malloc(sizeof(t_env_var));
	if (new_var == NULL)
		return (allocate_error(ALLOC_ERR), NULL);
	new_var->name = get_env_name(env_i);
	if (new_var->name == NULL)
		return (allocate_error(ALLOC_ERR), NULL);
	new_var->value = get_env_value(env_i);
	if (new_var->value == NULL)
		return (allocate_error(ALLOC_ERR), NULL);
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
		if (tmp_env_var->next == NULL)
			return (0);
		if (ft_strncmp(tmp_env_var->next->name, "USER", 4) == 0
			&& ft_strlen(tmp_env_var->next->name) == 4)
		{
			data->username = ft_strdup(tmp_env_var->next->value);
			if (data->username == NULL)
				return (allocate_error(ALLOC_ERR), 0);
		}
		tmp_env_var = tmp_env_var->next;
		i++;
	}
	return (1);
}

t_data	init_data(char **env, char *filelocation)
{
	t_data	data;

	data.commands = NULL;
	data.splitted_cmds = NULL;
	data.program_path = NULL;
	data.tmp_path = NULL;
	data.count_line = 0;
	data.exit_status = 0;
	if (put_env_to_data(&data, env) == 0)
	{
		free_data(&data);
		exit(1);
	}
	get_program_path(&data, filelocation);
	return (data);
}
