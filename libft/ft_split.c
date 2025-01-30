/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:41:00 by tprovost          #+#    #+#             */
/*   Updated: 2024/10/25 12:00:44 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

static int	ft_malloc(char **tab, const char *s, char c, int k)
{
	int	i;
	int	j;
	int	l;

	j = 0;
	l = 0;
	while (j < k)
	{
		while (s[l] == c)
			l++;
		i = 0;
		while (s[l + i] != '\0' && s[l + i] != c)
			i++;
		tab[j] = malloc ((i + 1) * sizeof(char));
		if (tab[j] == NULL)
			return (j);
		l = l + i;
		j++;
	}
	return (-1);
}

static int	ft_check(char **tab, const char *s, char c, int k)
{
	int	j;
	int	n;

	j = 0;
	n = ft_malloc(tab, s, c, k);
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

static void	remp_split(char **tab, const char *s, char c, int k)
{
	int	i;
	int	j;
	int	l;

	i = 0;
	j = 0;
	l = 0;
	while (j < k)
	{
		while (s[i] == c)
			i++;
		l = i;
		while (s[i] != '\0' && s[i] != c)
		{
			tab[j][i - l] = s[i];
			i++;
		}
		tab[j][i - l] = '\0';
		j++;
	}
	tab[k] = NULL;
}

char	**ft_split(const char *s, char c)
{
	int		i;
	int		j;
	int		k;
	char	**tab;

	i = 0;
	j = -1;
	k = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			k++;
		i++;
	}
	tab = (char **) malloc ((k + 1) * sizeof(char *));
	if (tab == NULL)
		return (NULL);
	if (ft_check(tab, s, c, k) == 0)
	{
		return (NULL);
	}
	remp_split(tab, s, c, k);
	return (tab);
}
/*
int	main(void)
{
	char	**str = ft_split(" salut je m'appelle titouan ", ' ');
	int	i = 0;
	
	while (str[i] != NULL)
	{
		printf("%d : |%s|\n", i, str[i]);
		free(str[i]);
		i++;
	}
	free(str[i]);
	free(str);
}*/
