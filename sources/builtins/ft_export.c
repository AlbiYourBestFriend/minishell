/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:08:23 by mleproux          #+#    #+#             */
/*   Updated: 2025/02/25 16:46:30 by tprovost         ###   ########.fr       */
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

static int	assign_value(t_env_var *tmp_var, char **tab, int i)
{
	char	*tmp;

	if (tmp_var->status == 1)
	{
		tmp = ft_strjoin(tmp_var->name, "=");
		if (tmp == NULL)
			return (-1);
		tab[i] = ft_strjoin(tmp, "\"");
		free(tmp);
		if (tab[i] == NULL)
			return (-1);
		if (tmp_var->value == NULL)
		{
			tmp = tab[i];
			tab[i] = ft_strjoin(tmp, "\"");
			free(tmp);
			if (tab[i] == NULL)
				return (-1);
		}
		else
		{
			tmp = tab[i];
			tab[i] = ft_strjoin(tmp, tmp_var->value);
			free(tmp);
			if (tab[i] == NULL)
				return (-1);
			tmp = tab[i];
			tab[i] = ft_strjoin(tmp, "\"");
			free(tmp);
			if (tab[i] == NULL)
				return (-1);
		}
		i++;
	}
	return (i);
}

static char	**export_lst_to_tab(t_env_var *env_var)
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
		return (NULL);
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

static void	print_export(t_data *data)
{
	int		i;
	int		j;
	char	**tab;

	i = 0;
	tab = export_lst_to_tab(data->env_variables);
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
			printf("declare -x %s\n", tab[i]);
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
		i = 0;
		while (cmd->args[++i] != NULL)
		{
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
				perror("invalid argument");
				break ;
			}
		}
	}
}
