/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 12:39:43 by mleproux          #+#    #+#             */
/*   Updated: 2025/02/06 13:24:34 by mleproux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_if_in_str(char *s, int index, int current_result)
{
	int	result;

	result = is_in_str(s, index);
	if (result == 1 && current_result == 0)
		return (1);
	else if (result == 0 && current_result == 1)
		return (0);
	else if (current_result == -1)
		return (result);
	return (current_result);
}

static size_t	ft_countstr(char *s, char c, size_t len)
{
	size_t	index;
	size_t	count;
	int		boolean;

	index = 0;
	count = 0;
	boolean = 0;
	while (index < len)
	{
		boolean = check_if_in_str(s, index, boolean);
		if (s[index] != c)
		{
			if (!boolean)
			{
				count++;
				boolean = 1;
			}
		}
		else
			boolean = 0;
		index++;
	}
	return (count);
}

static	size_t	ft_getsep(char *s, char c, size_t start, size_t len)
{
	size_t	index;

	index = start;
	while (index < len && s[index] != c && check_if_in_str(s, index, -1))
		index++;
	return (index);
}

static char	**ft_strsbuild(char *s, char c, char **strs, size_t len)
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

char	**pipe_split(char *s, char c)
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
// int	main(void)
// {
// 	int	index;

// 	index = 0;
// 	char **splitted;
// 	splitted = pipe_split("echo \"test | || test |\" | cat caca 'lol|lol'", '|');
// 	while(splitted[index])
// 	{
// 		printf("%s\n", splitted[index]);
// 		index++;
// 	}
// }