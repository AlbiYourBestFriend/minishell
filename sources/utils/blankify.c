/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blankify.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:37:55 by mleproux          #+#    #+#             */
/*   Updated: 2025/02/26 15:38:12 by mleproux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	blankify(char *str, int start, int len)
{
	while (len > start && str[start] != '\0')
	{
		str[start] = ' ';
		start++;
	}
}