/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blankify.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:37:55 by mleproux          #+#    #+#             */
/*   Updated: 2025/02/27 17:29:40 by tprovost         ###   ########.fr       */
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
