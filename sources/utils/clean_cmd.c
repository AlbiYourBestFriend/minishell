/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 12:56:42 by tprovost          #+#    #+#             */
/*   Updated: 2025/03/13 13:02:02 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	count_str_char(char *cmd, int i)
{
	char	quote;
	int		n;

	quote = cmd[i];
	i++;
	n = 1;
	while (cmd[i] != quote && cmd[i] != '\0')
	{
		i++;
		n++;
	}
	if (cmd[i] == quote)
		n++;
	return (n);
}

static int	nb_char(char *cmd)
{
	int		i;
	int		n;

	i = 0;
	n = 0;
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '\"' || cmd[i] == '\'')
		{
			n = n + count_str_char(cmd, i);
			i = i + count_str_char(cmd, i);
		}
		else
		{
			if (ft_isspace(cmd[i]) == 0
				|| (ft_isspace(cmd[i]) == 1 && ft_isspace(cmd[i + 1]) == 0
					&& cmd[i + 1] != '\0'))
				n++;
			i++;
		}
	}
	return (n);
}

static int	remp_str(char *cmd, int i, char *str, int n)
{
	char	quote;
	int		count;

	quote = cmd[i];
	count = 0;
	str[n] = cmd[i];
	count++;
	while (cmd[i + count] != quote && cmd[i + count] != '\0')
	{
		str[n + count] = cmd[i + count];
		count++;
	}
	if (cmd[i + count] == quote)
		str[n + count] = cmd[i + count];
	return (count);
}

static void	do_remp_str(char *cmd, int *i, char *str, int *n)
{
	int		count;

	count = 0;
	if (cmd[(*i)] == '\"' || cmd[(*i)] == '\'')
	{
		count = remp_str(cmd, (*i), str, (*n));
		if (cmd[(*i) + count] != '\0')
			(*n)++;
		(*n) = (*n) + count;
		(*i) = (*i) + count;
	}
	else
	{
		if (ft_isspace(cmd[(*i)]) == 0)
			str[(*n)] = cmd[(*i)];
		else if (ft_isspace(cmd[(*i)]) == 1 && ft_isspace(cmd[(*i) + 1]) == 0
			&& cmd[(*i) + 1] != '\0')
			str[(*n)] = ' ';
		if (ft_isspace(cmd[(*i)]) == 0
			|| (ft_isspace(cmd[(*i)]) == 1 && ft_isspace(cmd[(*i) + 1]) == 0
				&& cmd[(*i) + 1] != '\0'))
			(*n)++;
	}
}

char	*clean_cmd(char *cmd)
{
	char	*str;
	int		i;
	int		n;

	str = malloc((nb_char(cmd) + 1) * sizeof(char));
	if (str == NULL)
		return (printf("%s%s\n", ERREUR, ALLOC_ERR), NULL);
	i = 0;
	n = 0;
	while (ft_isspace(cmd[i]) == 1)
		i++;
	while (cmd[i] != '\0')
	{
		do_remp_str(cmd, &i, str, &n);
		if (cmd[i] != '\0')
			i++;
	}
	str[n] = '\0';
	free(cmd);
	return (str);
}
