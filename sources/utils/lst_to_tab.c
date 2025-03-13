/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_to_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:57:19 by tprovost          #+#    #+#             */
/*   Updated: 2025/03/13 20:00:14 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	put_value_to_tab_i(t_env_var *tmp_var, char **tab, int *i)
{
	char	*tmp;

	if (tmp_var->status == 1)
	{
		tmp = ft_strjoin(tmp_var->name, "=");
		if (tmp_var->value == NULL)
		{
			tab[*i] = tmp;
			if (tmp == NULL)
				return (allocate_error(ALLOC_ERR));
		}
		else
		{
			if (tmp == NULL)
			{
				tab[*i] = NULL;
				return (allocate_error(ALLOC_ERR));
			}
			tab[*i] = ft_strjoin(tmp, tmp_var->value);
			free(tmp);
			if (tab[*i] == NULL)
				return (allocate_error(ALLOC_ERR));
		}
		(*i)++;
	}
}

static char	**put_value(t_env_var *env_var, char **tab)
{
	int			i;
	t_env_var	*tmp_var;

	i = 0;
	tmp_var = env_var;
	while (tmp_var != NULL)
	{
		put_value_to_tab_i(tmp_var, tab, &i);
		if (i == -1)
			return (free_tab(tab), NULL);
		tmp_var = tmp_var->next;
	}
	tab[i] = NULL;
	return (tab);
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
	if (tab == NULL)
		return (allocate_error(ALLOC_ERR), NULL);
	return (put_value(env_var, tab));
}
