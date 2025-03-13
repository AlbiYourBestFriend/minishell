/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar_utils_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 19:19:48 by tprovost          #+#    #+#             */
/*   Updated: 2025/03/13 13:02:02 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	len_env_var_value_utils(char *cmd, int *i, int n)
{
	if (cmd[*i] == '?')
		return (exit_status_len(i) + n);
	if (ft_isdigit(cmd[*i]) == 1)
	{
		(*i)++;
		return (n);
	}
	if (ft_isalpha(cmd[*i]) == 0 && cmd[*i] != '_')
	{
		(*i)++;
		return (2 + n);
	}
	return (-1);
}

int	len_env_var_value(t_data *data, char *cmd, int *i, int n)
{
	int			l;
	int			j;
	char		*name;
	t_env_var	*env_var;

	j = 0;
	(*i)++;
	l = len_env_var_value_utils(cmd, i, n);
	if (l != -1)
		return (l);
	while (cmd[(*i) + j] != '\0' && ft_isspace(cmd[(*i) + j]) == 0
		&& cmd[(*i) + j] != '\"' && cmd[(*i) + j] != '\'')
		j++;
	name = ft_substr(cmd, *i, j);
	if (name == NULL)
		return (printf("%s%s\n", ERREUR, ALLOC_ERR), -1);
	env_var = get_env_var(data, name);
	(*i) += j;
	if (env_var != NULL)
		j = ft_strlen(env_var->value);
	else
		j = 0;
	free(name);
	return (j + n);
}

int	get_len_simple_quote(char *cmd, int *i, int n)
{
	int		len;

	len = 0;
	(*i)++;
	len++;
	while (cmd[(*i)] != '\'')
	{
		(*i)++;
		len++;
	}
	(*i)++;
	len++;
	return (len + n);
}

int	get_len_double_quote(t_data *data, char *cmd, int *i, int n)
{
	int		len;

	len = 0;
	(*i)++;
	len++;
	while (cmd[*i] != '\"')
	{
		if (cmd[*i] == '$')
		{
			len = len_env_var_value(data, cmd, i, n) - n;
		}
		else if (cmd[*i] != '\"')
		{
			(*i)++;
			len++;
		}
		if (len == -n - 1)
			return (-1);
	}
	(*i)++;
	len++;
	return (len + n);
}
