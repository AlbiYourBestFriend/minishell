/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env_var_utils_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:43:45 by tprovost          #+#    #+#             */
/*   Updated: 2025/02/12 17:13:23 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	copy_str(char *cmd, int *j, char *str, int *i)
{
	char	c;

	if (cmd[(*j)] == '\"' || cmd[(*j)] == '\'')
	{
		c = cmd[(*j)];
		(*j)++;
		while (cmd[(*j)] != c)
		{
			str[(*i)] = cmd[(*j)];
			(*i)++;
			(*j)++;
		}
	}
	else
	{
		str[(*i)] = cmd[(*j)];
		(*i)++;
	}
}

static int	get_name_utils(char *cmd, int *j)
{
	int	n;

	n = 0;
	while (ft_isspace(cmd[(*j)]) == 0 && (*j) > 0)
	{
		if (cmd[(*j)] == '\"' || cmd[(*j)] == '\'')
		{
			(*j) = skip_quote(cmd, (*j), -1);
			n = n + 2;
		}
		if ((*j) != 0)
			(*j)--;
	}
	return (n);
}

char	*get_env_var_name(char *cmd)
{
	int		i;
	int		j;
	int		n;
	char	*name;

	i = -1;
	while (cmd[++i] != '=' && cmd[i] != '\0')
	{
		if (cmd[i] == '\"' || cmd[i] == '\'')
			i = skip_quote(cmd, i, 1);
	}
	j = i;
	n = get_name_utils(cmd, &j);
	if (ft_isspace(cmd[j]) == 0)
		j--;
	name = malloc((i - j - n + 1) * sizeof(char));
	i = 0;
	while (cmd[++j] != '=' && cmd[j] != '\0')
		copy_str(cmd, &j, name, &i);
	name[i] = '\0';
	return (name);
}

// a modifier pour gerer les \" entre les "..."
static void	get_value_utils(char *cmd, int *i, int *j, int *n)
{
	char	c;

	if (cmd[(*i)] == '\"' || cmd[(*i)] == '\'')
		(*i) = skip_quote(cmd, (*i), 1);
	else if (cmd[(*i)] == '=')
	{
		(*j) = (*i);
		while (cmd[++(*i)] != '\0' && ft_isspace(cmd[(*i)]) == 0)
		{
			if (cmd[(*i)] == '\"' || cmd[(*i)] == '\'')
			{
				c = cmd[(*i)];
				while (cmd[++(*i)] != c)
					(*n)++;
			}
			else
				(*n)++;
		}
	}
}

// a modifier pour gerer les \" entre les "..."
char	*get_env_var_value(char *cmd)
{
	int		i;
	int		j;
	int		n;
	char	*value;

	i = -1;
	n = -1;
	while (cmd[++i] != '\0' && n == -1)
		get_value_utils(cmd, &i, &j, &n);
	value = malloc((n + 1) * sizeof(char));
	n = 0;
	while (cmd[++j] != '\0' && ft_isspace(cmd[j]) == 0)
		copy_str(cmd, &j, value, &n);
	value[n] = '\0';
	return (value);
}
