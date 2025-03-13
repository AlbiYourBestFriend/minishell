/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:09:37 by mleproux          #+#    #+#             */
/*   Updated: 2025/03/13 14:21:06 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	word_len(char *str, int i)
{
	int		len;
	char	quote;

	quote = '\0';
	len = 0;
	while ((int)ft_strlen(str) > (i + len)
		&& ft_isspace(str[i + len]) == 0)
	{
		if (str[i] == '\"' || str[i] == '\'')
			quote = str[i];
		if (quote)
		{
			len++;
			while (str[i + len] != quote && str[i + len] != '\0')
				len++;
			if (str[i + len] == quote)
				len++;
		}
		len++;
	}
	return (len);
}

static char	*fill_word(char *str, char *word, int *i)
{
	char	quote;
	int		len;

	len = 0;
	quote = '\0';
	while (str[*i] != '\0' && ft_isspace(str[*i]) == 0)
	{
		if (str[*i] == '\"' || str[*i] == '\'')
			quote = str[*i];
		if (quote)
		{
			word[len++] = str[(*i)++];
			while (str[*i] != quote && str[*i] != '\0')
				word[len++] = str[(*i)++];
			word[len] = str[(*i)];
			quote = '\0';
		}
		word[len++] = str[(*i)++];
	}
	word[len] = '\0';
	return (word);
}

char	*get_next_word(char *str, int *i)
{
	char	*word;

	if (str == NULL || str[*i] == '\0')
		return (NULL);
	while (ft_isspace(str[*i]) == 1 && str[*i] != '\0')
		(*i)++;
	word = malloc(sizeof(char) * word_len(str, *i) + 1);
	if (word == NULL)
		return (allocate_error(ALLOC_ERR), NULL);
	word = fill_word(str, word, i);
	return (word);
}
