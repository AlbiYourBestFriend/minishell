/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arglen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 11:01:32 by mleproux          #+#    #+#             */
/*   Updated: 2025/02/25 14:39:27 by mleproux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	env_var_len(t_data *data, char *arg, int *i)
{
	int			j;
	char		*name;
	t_env_var	*env_var;

	j = 0;
	(*i)++;
	while (arg[(*i) + j] != '\0' && ft_isspace(arg[(*i) + j]) == 0
		&& arg[(*i) + j] != '\"' && arg[(*i) + j] != '\'')
		j++;
	name = ft_substr(arg, *i, j);
	if (!name)
		return (-1);
	env_var = get_env_var(data, name);
	(*i) += j;
	if (env_var != NULL)
		j = ft_strlen(env_var->value);
	free(name);
	return (j);
}

static int	double_quote_len(t_data *data, char *arg, int *i)
{
	int	len;

	len = 0;
	(*i)++;
	while (arg[*i] != '\"' && arg[*i] != '\0')
	{
		if (arg[*i] == '$' && ft_isspace(arg[(*i) + 1]) == 0)
			len += env_var_len(data, arg, i);
		else if (arg[(*i)] != '\0')
		{
			(*i)++;
			len++;
		}
	}
	if (arg[*i] == '\"')
		(*i)++;
	return (len);
}

static int	single_quote_len(char *arg, int *i)
{
	int	len;

	len = 0;
	(*i)++;
	while (arg[*i] != '\'' && arg[*i] != '\0')
	{
		(*i)++;
		len++;
	}
	if (arg[*i] == '\'')
		(*i)++;
	return (len);
}

int	arglen(t_data *data, char *arg)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while ((int)ft_strlen(arg) > i)
	{
		if (arg[i] == '\'')
			len += single_quote_len(arg, &i);
		else if (arg[i] == '\"')
			len += double_quote_len(data, arg, &i);
		else if (arg[i] == '$' && ft_isspace(arg[i + 1]) == 0)
			len += env_var_len(data, arg, &i);
		else
		{
			i++;
			len++;
		}
	}
	return (len);
}
