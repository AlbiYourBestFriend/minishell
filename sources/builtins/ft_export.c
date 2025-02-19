/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:08:23 by mleproux          #+#    #+#             */
/*   Updated: 2025/02/19 15:29:05 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	compare_var(char **str1, char **str2)
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

static void	print_export(t_data *data)
{
	int		i;
	int		j;
	char	**tab;

	i = 0;
	tab = lst_to_tab(data->env_variables);
	if (tab[0] == NULL)
		return ;
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
			printf("%s\n", tab[i]);
	}
	free_tab(tab);
}

void	ft_export(t_data *data, t_command *cmd)
{
	t_env_var	*env_var;
	int			n;
	int			i;

	if (tab_len(cmd->args) == 1)
		print_export(data);
	else
	{
		i = 1;
		while (cmd->args[i] != NULL)
		{
			n = is_env_var(cmd->args[1]);
			if (n != 0)
			{
				printf("n = %d\n", n);
				env_var = handle_env_var(data, cmd->args[i], n);
				printf("name = %s\nvalue = %s\nstatus = %d\n", env_var->name, env_var->value, env_var->status);
				if (n == 1 || n == -1)
				{
					if (env_var->status == 0)
						env_var->status = 1;
				}
			}
			else
				perror("invalid argument");
			i++;
		}
	}
	// ft_exit(data, NULL);
}
