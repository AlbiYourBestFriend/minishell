/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_to_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:57:19 by tprovost          #+#    #+#             */
/*   Updated: 2025/02/12 13:48:14 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**lst_to_tab(t_env_var *env_var)
{
	int			i;
	char		*tmp;
	char		**tab;
	t_env_var	*tmp_var;

	i = 0;
	tmp_var = env_var;
	while (tmp_var != NULL)
	{
		if (tmp_var->status == 1)
			i++;
		tmp_var = tmp_var->next;
	}
	tab = malloc((i + 1) * sizeof(char *));
	i = 0;
	tmp_var = env_var;
	while (tmp_var != NULL)
	{
		if (tmp_var->status	== 1)
		{
			tmp = ft_strjoin(env_var->name, "=");
			if (env_var->value == NULL)
				tab[i] = tmp;
			else
				tab[i] = ft_strjoin(tmp, env_var->value);
			free(tmp);
			i++;
		}
		tmp_var = tmp_var->next;
	}
	tab[i] = NULL;
	return (tab);
}
