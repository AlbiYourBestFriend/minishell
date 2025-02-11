/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:09:37 by mleproux          #+#    #+#             */
/*   Updated: 2025/02/11 17:16:41 by mleproux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	word_len(char *str, int index)
{
	int		len;
	char	quote;

	quote = '\0';
	len = 0;
	if (str[index] == '\"' || str[index] == '\'')
		quote = str[index];
	if (quote)
	{
		len++;
		while (str[index + len] != quote && str[index + len] != '\0')
			len++;
		if (str[index + len] == quote)
			len++;
	}
	else
		while (str[index + len] != '\0' && ft_isspace(str[index + len]) == 0)
			len++;
	return (len);
}

static char	*fill_word(char *str, char *word, int *index)
{
	char	quote;
	int		len;

	len = 0;
	quote = '\0';
	if (str[*index] == '\"' || str[*index] == '\'')
		quote = str[*index];
	if (quote)
	{
		word[len++] = str[(*index)++];
		while (str[*index] != quote && str[*index] != '\0')
			word[len++] = str[(*index)++];
		word[len++] = str[(*index)++];
	}
	else
	{
		while (str[*index] != '\0' && ft_isspace(str[*index]) == 0)
			word[len++] = str[(*index)++];
	}
	word[len] = '\0';
	return (word);
}

char	*get_next_word(char *str, int *index)
{
	char	*word;

	if (str == NULL || str[*index] == '\0')
		return (NULL);
	while (ft_isspace(str[*index]) == 1 && str[*index] != '\0')
		(*index)++;
	word = malloc(sizeof(char) * word_len(str, *index) + 1);
	if (word == NULL)
		return (NULL);
	word = fill_word(str, word, index);
	return (word);
}
