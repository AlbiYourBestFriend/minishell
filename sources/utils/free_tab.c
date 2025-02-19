/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 18:31:34 by tprovost          #+#    #+#             */
/*   Updated: 2025/02/18 11:08:25 by mleproux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_tab(char **tab)
{
	int	index;

	index = 0;
	if (!tab)
		return ;
	while (tab[index])
	{
		free(tab[index]);
		index++;
	}
	free(tab);
}
