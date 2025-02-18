/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:28:12 by tprovost          #+#    #+#             */
/*   Updated: 2025/02/18 16:30:16 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	root_return_utils(t_env_var *tmp, char *pwd)
{
	while (tmp != NULL && (ft_strncmp(tmp->name, "OLDPWD", 6) != 0
		|| ft_strlen(tmp->name) != 6))
		tmp = tmp->next;
	if (tmp != NULL)
	{
		if (tmp->value != NULL)
			free(tmp->value);
		tmp->value = pwd;
	}
	else
	{
		free(pwd);
		perror("oldpwd not found in env");
	}
}

void	root_return(t_data *data)
{
	int			n;
	char		*pwd;
	t_env_var	*tmp;

	tmp = data->env_variables;
	while (tmp != NULL
		&& (ft_strncmp(tmp->name, "PWD", 3) != 0 || ft_strlen(tmp->name) != 3))
		tmp = tmp->next;
	if (tmp != NULL && tmp->value != NULL && tmp->value[0] != '\0')
	{
		pwd = ft_strdup(tmp->value);
		n = 0;
		while (n < count_char(pwd, '/'))
		{
			chdir("..");
			n++;
		}
		tmp->value[0] = '/';
		tmp->value[1] = '\0';
		tmp = data->env_variables;
		root_return_utils(tmp, pwd);
	}
	else
		perror("pwd not found in env");
}
