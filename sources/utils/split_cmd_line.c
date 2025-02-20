/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 19:03:18 by tprovost          #+#    #+#             */
/*   Updated: 2025/02/19 15:48:10 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	remp_utils(char *tab_j, char *line, int i, int l)
{
	char	c;

	if (line[i] == '\"' || line[i] == '\'')
	{
		c = line[i];
		tab_j[i - l] = line[i];
		i++;
		while (line[i] != c && line[i] != '\0')
		{
			tab_j[i - l] = line[i];
			i++;
		}
		if (line[i] == c)
		{
			tab_j[i - l] = line[i];
			i++;
		}
	}
	else
	{
		tab_j[i - l] = line[i];
		i++;
	}
	return (i);
}

static char	**remp_split(char **tab, char *line, char c, int nb_word)
{
	int	i;
	int	j;
	int	l;

	i = 0;
	j = 0;
	l = 0;
	if (ft_check(tab, line, c, nb_word) == 0)
		return (NULL);
	while (j < nb_word)
	{
		while (line[i] == c)
			i++;
		l = i;
		while (line[i] != '\0' && line[i] != c)
		{
			i = remp_utils(tab[j], line, i, l);
		}
		tab[j][i - l] = '\0';
		j++;
	}
	tab[nb_word] = NULL;
	return (tab);
}

static int	count_word(char *l, char c, int i, int *nb_word)
{
	if (l[i] == '\"')
	{
		i++;
		while (l[i] != '\"' && l[i] != '\0')
			i++;
		if (l[i] == '\"')
			i++;
		while (l[i] != c && l[i] != '\"' && l[i] != '\'' && l[i] != '\0')
			i++;
		if (l[i] == c || l[i] == '\0')
			(*nb_word)++;
	}
	else if (l[i] == '\'')
	{
		i++;
		while (l[i] != '\'' && l[i] != '\0')
			i++;
		if (l[i] == '\'')
			i++;
		while (l[i] != c && l[i] != '\'' && l[i] != '\"' && l[i] != '\0')
			i++;
		if (l[i] == c || l[i] == '\0')
			(*nb_word)++;
	}
	return (i);
}

char	**split_cmd_line(char *line, char c)
{
	int		i;
	int		nb_word;
	char	**tab;

	i = 0;
	nb_word = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\"' || line[i] == '\'')
			i = count_word(line, c, i, &nb_word);
		else
		{
			if (line[i] != c && (line[i + 1] == c || line[i + 1] == '\0')
				&& (i == 0 || (line[i - 1] != '\"' && line[i - 1] != '\'')))
				nb_word++;
			i++;
		}
	}
	tab = malloc((nb_word + 1) * sizeof(char *));
	return (remp_split(tab, line, c, nb_word));
}

// int	main(int argc, char **argv)
// {
// 	char *str;
// 	char **tab;
// 	int i;

// 	// str = readline("str : ");
// 	printf("len str : %zu\n", strlen(argv[1]));
// 	tab = split_cmd_line(argv[1], '|');
// 	i = 0;
// 	while (tab[i] != NULL)
// 	{
// 		printf("%s\n", tab[i]);
// 		i++;
// 	}
// 	free_tab(tab);
// 	return (0);
// }
