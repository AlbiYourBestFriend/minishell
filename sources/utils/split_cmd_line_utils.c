/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd_line_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:14:28 by tprovost          #+#    #+#             */
/*   Updated: 2025/02/18 14:03:50 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_len_word(char *line, int i, int l)
{
	if (line[l + i] == '\"')
	{
		i++;
		while (line[l + i] != '\"' && line[l + i] != '\0')
			i++;
		if (line[l + i] == '\"')
			i++;
	}
	else if (line[l + i] == '\'')
	{
		i++;
		while (line[l + i] != '\'' && line[l + i] != '\0')
			i++;
		if (line[l + i] == '\'')
			i++;
	}
	else
		i++;
	return (i);
}

static int	malloc_words(char **tab, char *line, char c, int nb_word)
{
	int	i;
	int	j;
	int	l;

	j = 0;
	l = 0;
	while (j < nb_word)
	{
		while (line[l] == c)
			l++;
		i = 0;
		while (line[l + i] != '\0' && line[l + i] != c)
		{
			i = get_len_word(line, i, l);
		}
		tab[j] = malloc ((i + 1) * sizeof(char));
		if (tab[j] == NULL)
			return (j);
		l = l + i;
		j++;
	}
	return (-1);
}

int	ft_check(char **tab, char *line, char c, int k)
{
	int	j;
	int	n;

	j = 0;
	if (tab == NULL)
		return (0);
	n = malloc_words(tab, line, c, k);
	if (n == -1)
		return (1);
	while (j < n)
	{
		free(tab[j]);
		j++;
	}
	free(tab);
	return (0);
}
