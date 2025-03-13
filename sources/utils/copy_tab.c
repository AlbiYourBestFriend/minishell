/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_tab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:12:57 by tprovost          #+#    #+#             */
/*   Updated: 2025/03/13 14:21:06 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**copy_tab(char **tab)
{
	char	**copy;
	int		len;
	int		i;

	len = tab_len(tab);
	if (len == -1)
		return (NULL);
	copy = malloc((len + 1) * sizeof(char *));
	if (copy == NULL)
		return (allocate_error(ALLOC_ERR), NULL);
	i = 0;
	while (tab[i] != NULL)
	{
		copy[i] = ft_strdup(tab[i]);
		if (copy[i] == NULL)
		{
			free_tab(tab);
			free_tab(copy);
			return (allocate_error(ALLOC_ERR), NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}
