/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env_var_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:20:14 by tprovost          #+#    #+#             */
/*   Updated: 2025/02/12 11:10:48 by mleproux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_env_var(char *cmd)
{
	int	i;

	i = 0;
	if (cmd[i] > 32 && cmd[i] < 127)
		i++;
	else
		return (0);
	while (cmd[i] > 32 && cmd[i] < 127 && cmd[i] != '\0' && cmd[i] != '=')
		i++;
	if (cmd[i] != '=')
		return (0);
	i++;
	if (cmd[i] == '\0' || ft_isspace(cmd[i]) == 1)
		return (-1);
	return (1);
}

int	exist_var(t_data *data, char *name)
{
	int			n;
	int			i;
	t_env_var	*env_var;

	n = 0;
	env_var = data->env_variables;
	while (ft_strncmp(env_var->name, name, ft_strlen(name)) != 0
		&& ft_strlen(name) != ft_strlen(env_var->name)
		&& env_var != NULL)
		env_var = env_var->next;
	if (env_var != NULL)
		n++;
	i = 0;
	while (ft_strncmp(data->my_env[i], name, ft_strlen(name)) != 0
		&& data->my_env[i][ft_strlen(name)] != '='
		&& data->my_env[i] != NULL)
		i++;
	if (data->my_env[i] != NULL)
		n = n + 2;
	return (n);
}

void	add_env_var(t_data *data, char *name, char *value)
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
