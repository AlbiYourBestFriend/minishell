/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_tab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:12:57 by tprovost          #+#    #+#             */
/*   Updated: 2025/02/04 13:20:54 by mleproux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**copy_tab(char **tab)
{
	char	**copy;
	int		len;
	int		index;

	len = tab_len(tab);
	copy = malloc((len + 1) * sizeof(char *));
	if (!copy)
		return (NULL);
	index = 0;
	while (tab[index])
	{
		copy[index] = ft_strdup(tab[index]);
		if (!copy[index])
			return (free_tab(tab), NULL);
		index++;
	}
	copy[index] = NULL;
	return (copy);
}
