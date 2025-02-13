/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_word_count.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 15:11:01 by mleproux          #+#    #+#             */
/*   Updated: 2025/02/13 11:38:43 by mleproux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_past_quote(char *str, int i)
{
	char	quote;

	quote = str[i];
	i++;
	while (str[i] != quote && str[i] != '\0')
		i++;
	if (str[i] == quote)
		i++;
	return (i);
}

int	get_word_count(char *str)
{
	int		count;
	int		i;
	int		boolean;

	count = 0;
	i = 0;
	boolean = 0;
	while ((int)ft_strlen(str) > i)
	{
		if (str[i] != ' ')
		{
			if (boolean == 0)
			{
				boolean = 1;
				count++;
			}
		}
		else
			boolean = 0;
		if (str[i] == '\"' || str[i] == '\'')
			i = get_past_quote(str, i);
		else
			i++;
	}
	return (count);
}
