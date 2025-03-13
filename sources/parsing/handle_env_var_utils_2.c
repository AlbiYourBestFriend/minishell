/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env_var_utils_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:43:45 by tprovost          #+#    #+#             */
/*   Updated: 2025/03/13 13:44:54 by tprovost         ###   ########.fr       */
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
		while (cmd[(*j)] != c && cmd[(*j)] != '\0')
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
	if (name == NULL)
		return (printf("%s%s\n", ERREUR, ALLOC_ERR), NULL);
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
		while (cmd[++(*i)] != '\0')
		{
			if (cmd[(*i)] == '\"' || cmd[(*i)] == '\'')
			{
				c = cmd[(*i)];
				while (cmd[++(*i)] != c && cmd[(*i)] != '\0')
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

	i = 0;
	j = 0;
	n = -1;
	while (cmd[i] != '\0' && n == -1)
	{
		get_value_utils(cmd, &i, &j, &n);
		if (cmd[i] != '\0')
			i++;
	}
	value = malloc((n + 2) * sizeof(char));
	if (value == NULL)
		return (printf("%s%s\n", ERREUR, ALLOC_ERR), NULL);
	n = 0;
	while (cmd[++j] != '\0')
		copy_str(cmd, &j, value, &n);
	value[n] = '\0';
	return (value);
}
