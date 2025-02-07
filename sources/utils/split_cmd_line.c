/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 19:03:18 by tprovost          #+#    #+#             */
/*   Updated: 2025/02/06 18:17:27 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// char	**split_cmd_line(char *cmd)
// {
// 	int		i;
// 	int		j;
// 	int		n;
// 	int		c;
// 	char	**tab;

// 	i = 0;
// 	n = 0;
// 	while (cmd[i] != '\0')
// 	{
// 		c = is_in_str(cmd, i);
// 		if (c == 0 && ft_isspace(cmd[i]) == 0 && (ft_isspace(cmd[i + 1]) == 1 || cmd[i + 1] == '\0'))
// 			n++;
// 		i++;
// 	}
// 	tab = malloc ((n + 1) * sizeof(char *));
// 	i = 0;
// 	while (cmd[i] != '\0')
// 	{
// 		j = i;
// 		while (cmd[i] != '\0' && ft_isspace(cmd[i]) == 0)
// 			i++;
// 		if (cmd[i] != '\0')
// 			i++;
// 	}
// }





#include <stdlib.h>
#include <stdio.h>

static int	ft_malloc(char **tab, char *line, char c, int nb_word)
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
		while (line[l + i] != '\0' && line[l + i] != c) //  || is_in_str(line, l + i) == 1)
		{
			// printf("line[%d] : %c\n", l + i, line[l + i]);
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
		}
		tab[j] = malloc ((i + 1) * sizeof(char));
		printf("size tab[%d] : %d\n", j, i);
		if (tab[j] == NULL)
			return (j);
		l = l + i;
		j++;
	}
	return (-1);
}

static int	ft_check(char **tab, char *line, char c, int k)
{
	int	j;
	int	n;

	j = 0;
	n = ft_malloc(tab, line, c, k);
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

static void	remp_split(char **tab, char *line, char c, int nb_word)
{
	int	i;
	int	j;
	int	l;

	i = 0;
	j = 0;
	l = 0;
	while (j < nb_word)
	{
		while (line[i] == c)
			i++;
		l = i;
		while (line[i] != '\0' && line[i] != c)
		{
			if (line[i] == '\"')
			{
				tab[j][i - l] = line[i];
				i++;
				while (line[i] != '\"' && line[i] != '\0')
				{
					tab[j][i - l] = line[i];
					i++;
				}
				if (line[i] == '\"')
				{
					tab[j][i - l] = line[i];
					i++;
				}
			}
			else if (line[i] == '\'')
			{
				tab[j][i - l] = line[i];
				i++;
				while (line[i] != '\'' && line[i] != '\0')
				{
					tab[j][i - l] = line[i];
					i++;
				}
				if (line[i] == '\'')
				{
					tab[j][i - l] = line[i];
					i++;
				}
			}
			else
			{
				tab[j][i - l] = line[i];
				i++;
			}
		}
		tab[j][i - l] = '\0';
		printf("tab[%d] : %s\n", j, tab[j]);
		j++;
	}
	tab[nb_word] = NULL;
	printf("tab[%d] : %s\n", j, tab[j]);
}

char	**split_cmd_line(char *line, char c)
{
	int		i;
	int		j;
	int		nb_word;
	char	**tab;

	i = 0;
	j = -1;
	nb_word = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\"')
		{
			i++;
			while (line[i] != '\"' && line[i] != '\0')
				i++;
			if (line[i] == '\"')
				i++;
			nb_word++;
		}
		else if (line[i] == '\'')
		{
			i++;
			while (line[i] != '\'' && line[i] != '\0')
				i++;
			if (line[i] == '\'')
				i++;
			nb_word++;
		}
		else
		{
			if (line[i] != c && (line[i + 1] == c || line[i + 1] == '\0'))
				nb_word++;
			i++;
		}
	}
	printf("len line : %d\n", i);
	printf("nb word : %d\n", nb_word);
	tab = malloc ((nb_word + 1) * sizeof(char *));
	if (tab == NULL)
		return (NULL);
	if (ft_check(tab, line, c, nb_word) == 0)
		return (NULL);
	remp_split(tab, line, c, nb_word);
	return (tab);
}

int	main(void)
{
	char	*str = readline("minishell : ");
	split_cmd_line(str, '|');
	// int	i = 0;
	
	// while (str[i] != NULL)
	// {
	// 	printf("%d : %s\n", i, str[i]);
	// 	free(str[i]);
	// 	i++;
	// }
	// free(str[i]);
	// free(str);
}
