/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:28:16 by tprovost          #+#    #+#             */
/*   Updated: 2025/04/07 13:57:10 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// ecrit la valeur de l'exit
int	put_exit_status(char *str, int *i_n)
{
	int		i;
	char	*exit;

	i = 0;
	exit = ft_itoa(g_exit_status);
	if (exit == NULL)
	{
		allocate_error(ALLOC_ERR);
		return (0);
	}
	while (exit[i] != '\0')
	{
		copy_and_inc(str, &i_n[1], exit, &i);
	}
	free(exit);
	i_n[0] += 2;
	return (1);
}

static int	put_env_var_value_2(char *cmd, char *str, int *i_n)
{
	if (cmd[i_n[0]] == '$' && cmd[i_n[0] + 1] == '?')
		return (put_exit_status(str, i_n));
	if (ft_isspace(cmd[i_n[0] + 1]) == 1
		|| cmd[i_n[0] + 1] == '\"' || cmd[i_n[0] + 1] == '\''
		|| cmd[i_n[0] + 1] == '$' || cmd[i_n[0] + 1] == '\0')
	{
		copy_and_inc(str, &i_n[1], cmd, &i_n[0]);
		return (1);
	}
	if (ft_isdigit(cmd[i_n[0] + 1]) == 1)
	{
		i_n[0]++;
		i_n[0]++;
		return (1);
	}
	if (ft_isalpha(cmd[i_n[0] + 1]) == 0 && cmd[i_n[0] + 1] != '_')
	{
		copy_and_inc(str, &i_n[1], cmd, &i_n[0]);
		copy_and_inc(str, &i_n[1], cmd, &i_n[0]);
		return (1);
	}
	i_n[0]++;
	return (0);
}

// ecrit la valeur de la variable
int	put_env_var_value(t_data *data, char *cmd, char *str, int *i_n)
{
	int			j;
	char		*name;
	t_env_var	*env_var;

	if (put_env_var_value_2(cmd, str, i_n) == 1)
		return (1);
	j = 0;
	while (ft_isspace(cmd[i_n[0] + j]) == 0
		&& cmd[i_n[0] + j] != '\"' && cmd[i_n[0] + j] != '\''
		&& cmd[i_n[0] + j] != '$' && cmd[i_n[0] + j] != '\0')
		j++;
	name = ft_substr(cmd, i_n[0], j);
	if (name == NULL)
		return (allocate_error(ALLOC_ERR), 0);
	i_n[0] += j;
	env_var = get_env_var(data, name);
	if (env_var != NULL && env_var->value != NULL)
	{
		j = 0;
		while (env_var->value[j] != '\0')
			copy_and_inc(str, &i_n[1], env_var->value, &j);
	}
	return (free(name), 1);
}

// ecrit ce qu'il y a dans les ''
void	put_simple_quote(char *cmd, char *str, int *i_n)
{
	copy_and_inc(str, &i_n[1], cmd, &i_n[0]);
	while (cmd[i_n[0]] && cmd[i_n[0]] != '\'')
	{
		copy_and_inc(str, &i_n[1], cmd, &i_n[0]);
	}
	str[i_n[1]] = cmd[i_n[0]];
	if (cmd[i_n[0]] == '\"')
	{
		copy_and_inc(NULL, &i_n[1], NULL, &i_n[0]);
	}
}

// ecrit ce qu'il y a dans les ""
int	put_double_quote(t_data *data, char *cmd, char *str, int *i_n)
{
	copy_and_inc(str, &i_n[1], cmd, &i_n[0]);
	while (cmd[i_n[0]] != '\0' && cmd[i_n[0]] != '\"')
	{
		if (cmd[i_n[0]] == '$')
			if (put_env_var_value(data, cmd, str, i_n) == 0)
				return (0);
		if (cmd[i_n[0]] != '\"' && cmd[i_n[0]] != '$')
		{
			copy_and_inc(str, &i_n[1], cmd, &i_n[0]);
		}
	}
	str[i_n[1]] = cmd[i_n[0]];
	if (cmd[i_n[0]] == '\"')
	{
		copy_and_inc(NULL, &i_n[1], NULL, &i_n[0]);
	}
	return (1);
}
