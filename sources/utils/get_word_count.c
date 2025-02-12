/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_word_count.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 15:11:01 by mleproux          #+#    #+#             */
/*   Updated: 2025/02/12 16:21:26 by mleproux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_past_quote(char *str, int index)
{
	char	quote;

	quote = str[index];
	index++;
	while (str[index] != quote && str[index] != '\0')
		index++;
	if (str[index] == quote)
		index++;
	return (index);
}

int	get_word_count(char *str)
{
	int		count;
	int		index;
	int		boolean;

	count = 0;
	index = 0;
	boolean = 0;
	while (str[index] != '\0')
	{
		if (str[index] != ' ')
		{
			if (boolean == 0)
			{
				boolean = 1;
				count++;
			}
		}
		else
			boolean = 0;
		if (str[index] == '\"' || str[index] == '\'')
			index = get_past_quote(str, index);
		index++;
	}
	return (count);
}
