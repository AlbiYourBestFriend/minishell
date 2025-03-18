/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:08:23 by mleproux          #+#    #+#             */
/*   Updated: 2025/03/18 10:33:43 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// transforme l'environnement en un tableau de chaines de caracteres
// avec la vauer de la variable entre guillemets
static char	**export_lst_to_tab(t_env_var *env_var, int i)
{
	char		**tab;
	t_env_var	*tmp_var;

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
	i = 0;
	tmp_var = env_var;
	while (tmp_var != NULL)
	{
		i = assign_value(tmp_var, tab, i);
		if (i < 0)
			return (free_tab(tab), NULL);
		tmp_var = tmp_var->next;
	}
	tab[i] = NULL;
	return (tab);
}

// handle export sans argument
// print les variables d'environnement dans l'ordre alphabetique
static int	print_export(t_data *data)
{
	int		i;
	int		j;
	char	**tab;

	i = 0;
	tab = export_lst_to_tab(data->env_variables, i);
	if (tab == NULL)
		return (0);
	while (tab[i + 1] != NULL)
	{
		j = i + 1;
		while (tab[j] != NULL)
		{
			compare_var(&tab[i], &tab[j]);
			j++;
		}
		i++;
	}
	i = -1;
	while (tab[++i] != NULL)
	{
		if (tab[i][0] != '_' || tab[i][1] != '=')
			printf("declare -x %s\n", tab[i]);
	}
	return (free_tab(tab), 1);
}

static int	ft_export_utils(t_data *data, t_command *cmd, int i)
{
	t_env_var	*env_var;
	int			n;

	n = is_env_var(cmd->args[i]);
	if (n != 0)
	{
		env_var = handle_env_var(data, cmd->args[i], n);
		if (env_var != NULL && (n == 1 || n == -1)
			&& env_var->status == 0)
			env_var->status = 1;
	}
	else
	{
		g_exit_status = 1;
		printf("%sexport: `%s': %s\n", ERROR, cmd->args[i], INVALID_ID);
		return (0);
	}
	return (1);
}

int	ft_export(t_data *data, t_command *cmd)
{
	int			i;

	if (tab_len(cmd->args) == 1)
		print_export(data);
	else
	{
		i = 1;
		while (cmd->args[i] != NULL)
		{
			if (ft_export_utils(data, cmd, i) == 0)
			{
				return (0);
			}
			i++;
		}
	}
	return (1);
}
