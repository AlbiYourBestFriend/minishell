/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_tab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:12:57 by tprovost          #+#    #+#             */
/*   Updated: 2025/02/04 12:57:29 by mleproux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**copy_tab(char **tab)
{
	char	**copy;
	int		len;
	int		i;

	len = tab_len(tab);
	copy = malloc((len + 1) * sizeof(char *));
	i = 0;
	while (i < len)
	{
		copy[i] = ft_strdup(tab[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}
