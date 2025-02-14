/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_to_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:57:19 by tprovost          #+#    #+#             */
/*   Updated: 2025/02/13 18:08:26 by mleproux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	assign_value(t_env_var *tmp_var, char **tab, int i)
{
	char	*tmp;

	if (tmp_var->status == 1)
	{
		tmp = ft_strjoin(tmp_var->name, "=");
		if (tmp_var->value == NULL)
			tab[i] = tmp;
		else
			tab[i] = ft_strjoin(tmp, tmp_var->value);
		free(tmp);
		i++;
	}
	return (i);
}

char	**lst_to_tab(t_env_var *env_var)
{
	int			i;
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
		i = assign_value(tmp_var, tab, i);
		tmp_var = tmp_var->next;
	}
	tab[i] = NULL;
	return (tab);
}
