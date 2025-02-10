/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:09:37 by mleproux          #+#    #+#             */
/*   Updated: 2025/02/10 18:09:56 by mleproux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	word_len(char *cmd, int index)
{
	int	len;
	
	len = 0;
	while (cmd[index + len] != '\0' && ft_isspace(cmd[index + len]) == 0)
    {
        len++;
    }
	return (len);
}
	
char	*get_next_word(char *cmd, int *index)
{
	char	*word;
	int		len;
	if (cmd == NULL || cmd[*index] == '\0')
		return (NULL);
	while (ft_isspace(cmd[*index]) == 1)
		(*index)++;
	word = malloc(sizeof(char) * word_len(cmd, *index) + 1);
	if (word == NULL)
		return (NULL);
	len = 0;
	while (cmd[*index + len] != '\0' && ft_isspace(cmd[*index + len]) == 0)
	{
		word[len] = cmd[*index + len];
		len++; 
	}
	word[len] = '\0';
	*index += len;
	return (word);
}