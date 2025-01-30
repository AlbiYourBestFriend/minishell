/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 11:07:56 by mleproux          #+#    #+#             */
/*   Updated: 2024/10/25 11:48:46 by mleproux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_countstr(char const *s, char c, size_t len)
{
	size_t	index;
	size_t	count;
	int		bool;

	index = 0;
	count = 0;
	bool = 0;
	while (index < len)
	{
		if (s[index] != c)
		{
			if (!bool)
			{
				count++;
				bool = 1;
			}
		}
		else
			bool = 0;
		index++;
	}
	return (count);
}

static	size_t	ft_getsep(char const *s, char c, size_t start, size_t len)
{
	size_t	index;

	index = start;
	while (index < len && s[index] != c)
		index++;
	return (index);
}

static char	**ft_strsbuild(char const *s, char c, char **strs, size_t len)
{
	size_t	index;
	size_t	start;

	index = 0;
	start = 0;
	while (index < ft_countstr(s, c, len))
	{
		while (start < len && s[start] == c)
			start++;
		strs[index] = ft_substr(s, start, ft_getsep(s, c, start, len) - start);
		if (!strs[index])
		{
			while (index > 0)
				free(strs[--index]);
			free(strs);
			return (NULL);
		}
		start = ft_getsep(s, c, start, len) + 1;
		index++;
	}
	strs[ft_countstr(s, c, len)] = NULL;
	return (strs);
}

char	**ft_split(char const *s, char c)
{
	char		**strs;
	size_t		len;
	size_t		count;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	count = ft_countstr(s, c, len);
	strs = malloc((count + 1) * sizeof(char *));
	if (!strs)
		return (NULL);
	strs = ft_strsbuild(s, c, strs, len);
	return (strs);
}
/*
int	main(void)
{
	char	**lists;
	int		index;

	lists = ft_split("Hello\0les\0amis\0!", '\0');
	index = 0;
	while (lists[index] != NULL)
	{
		printf("%s\n", lists[index]);

		index++;
	}
	return (0);
}
*/