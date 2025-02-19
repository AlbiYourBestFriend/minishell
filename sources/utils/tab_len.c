/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_len.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:02:16 by mleproux          #+#    #+#             */
/*   Updated: 2025/02/19 12:23:49 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	tab_len(char **tab)
{
	int	i;

	i = 0;
	if (tab == NULL)
		return (-1);
	while (tab[i] != NULL)
		i++;
	return (i);
}
