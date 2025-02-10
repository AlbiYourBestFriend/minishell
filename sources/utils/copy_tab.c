/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_tab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:12:57 by tprovost          #+#    #+#             */
/*   Updated: 2025/02/10 15:09:02 by tprovost         ###   ########.fr       */
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
	if (!copy)
		return (NULL);
	i = 0;
	while (tab[i])
	{
		copy[i] = ft_strdup(tab[i]);
		if (copy[i] == '\0')
			return (free_tab(tab), NULL);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}
