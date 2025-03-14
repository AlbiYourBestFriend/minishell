/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:28:16 by tprovost          #+#    #+#             */
/*   Updated: 2025/03/14 11:43:08 by mleproux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
		str[i_n[1]] = exit[i];
		i_n[1]++;
		i++;
	}
	free(exit);
	i_n[0] += 2;
	return (1);
}

static int	put_env_var_value_utils(char *cmd, char *str, int *i_n)
{
	if (ft_isdigit(cmd[i_n[0] + 1]) == 1)
	{
		i_n[0]++;
		i_n[0]++;
		return (1);
	}
	if (ft_isalpha(cmd[i_n[0] + 1]) == 0 && cmd[i_n[0] + 1] != '_')
	{
		str[i_n[1]] = cmd[i_n[0]];
		i_n[0]++;
		i_n[1]++;
		str[i_n[1]] = cmd[i_n[0]];
		i_n[0]++;
		i_n[1]++;
		return (1);
	}
	i_n[0]++;
	return (0);
}

int	put_env_var_value(t_data *data, char *cmd, char *str, int *i_n)
{
	int			j;
	char		*name;
	t_env_var	*env_var;

	if (put_env_var_value_utils(cmd, str, i_n) == 1)
		return (1);
	j = 0;
	while (cmd[i_n[0] + j] != '\0' && ft_isspace(cmd[i_n[0] + j]) == 0
		&& cmd[i_n[0] + j] != '\"' && cmd[i_n[0] + j] != '\'' && cmd[i_n[0] + j] != '$')
		j++;
	name = ft_substr(cmd, i_n[0], j);
	if (name == NULL)
		return (allocate_error(ALLOC_ERR), 0);
	i_n[0] += j;
	env_var = get_env_var(data, name);
	if (env_var != NULL)
	{
		j = -1;
		while (env_var->value[++j] != '\0')
		{
			str[i_n[1]] = env_var->value[j];
			i_n[1]++;
		}
	}
	return (free(name), 1);
}

void	put_simple_quote(char *cmd, char *str, int *i_n)
{
	str[i_n[1]] = cmd[i_n[0]];
	i_n[0]++;
	i_n[1]++;
	while (cmd[i_n[0]] && cmd[i_n[0]] != '\'')
	{
		str[i_n[1]] = cmd[i_n[0]];
		i_n[0]++;
		i_n[1]++;
	}
	str[i_n[1]] = cmd[i_n[0]];
	if (cmd[i_n[0]] == '\"')
	{
		i_n[0]++;
		i_n[1]++;
	}
}

int	put_double_quote(t_data *data, char *cmd, char *str, int *i_n)
{
	str[i_n[1]] = cmd[i_n[0]];
	i_n[0]++;
	i_n[1]++;
	while (cmd[i_n[0]] && cmd[i_n[0]] != '\"')
	{
		if (cmd[i_n[0]] == '$')
			if (put_env_var_value(data, cmd, str, i_n) == 0)
				return (0);
		if (cmd[i_n[0]] != '\"')
		{
			str[i_n[1]] = cmd[i_n[0]];
			i_n[0]++;
			i_n[1]++;
		}
	}
	str[i_n[1]] = cmd[i_n[0]];
	if (cmd[i_n[0]] == '\"')
	{
		i_n[0]++;
		i_n[1]++;
	}
	return (1);
}
