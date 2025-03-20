/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 12:03:03 by tprovost          #+#    #+#             */
/*   Updated: 2025/03/20 15:02:14 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	compare_var(char **str1, char **str2)
{
	int		i;
	char	*tmp;

	i = 0;
	while ((*str1)[i] != '=' && (*str2)[i] != '=' && (*str1)[i] == (*str2)[i])
		i++;
	if ((*str1)[i] == '=')
		return ;
	if ((*str2)[i] == '=' || (*str1)[i] > (*str2)[i])
	{
		tmp = (*str1);
		(*str1) = (*str2);
		(*str2) = tmp;
	}
}

static int	assign_value_utils(t_env_var *tmp_var, char **tab, char *tmp, int i)
{
	tmp = tab[i];
	tab[i] = ft_strjoin(tmp, tmp_var->value);
	free(tmp);
	if (tab[i] == NULL)
		return (allocate_error(ALLOC_ERR), -1);
	tmp = tab[i];
	tab[i] = ft_strjoin(tmp, "\"");
	free(tmp);
	if (tab[i] == NULL)
		return (allocate_error(ALLOC_ERR), -1);
	return (0);
}

int	assign_value(t_env_var *tmp_var, char **tab, int i)
{
	char	*tmp;

	if (tmp_var->status == 1)
	{
		tmp = ft_strjoin(tmp_var->name, "=");
		if (tmp == NULL)
			return (allocate_error(ALLOC_ERR), -1);
		tab[i] = ft_strjoin(tmp, "\"");
		free(tmp);
		if (tab[i] == NULL)
			return (allocate_error(ALLOC_ERR), -1);
		if (tmp_var->value == NULL)
		{
			tmp = tab[i];
			tab[i] = ft_strjoin(tmp, "\"");
			free(tmp);
			if (tab[i] == NULL)
				return (allocate_error(ALLOC_ERR), -1);
		}
		else if (assign_value_utils(tmp_var, tab, tmp, i) == -1)
			return (-1);
	}
	else if ((tab[i] = ft_strdup(tmp_var->name)) == NULL)
		return (allocate_error(ALLOC_ERR), -1);
	return (i + 1);
}
