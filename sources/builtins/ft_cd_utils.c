/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:28:12 by tprovost          #+#    #+#             */
/*   Updated: 2025/02/25 16:26:36 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	root_return_utils(t_env_var *tmp, char *pwd)
{
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

	tmp = get_env_var(data, "PWD");
	if (tmp != NULL && tmp->value != NULL && tmp->value[0] != '\0')
	{
		pwd = ft_strdup(tmp->value);
		if (pwd == NULL)
			return ;
		n = 0;
		while (n < count_char(pwd, '/'))
		{
			chdir("..");
			n++;
		}
		tmp->value[0] = '/';
		tmp->value[1] = '\0';
		tmp = get_env_var(data, "OLDPWD");
		root_return_utils(tmp, pwd);
	}
	else
		perror("pwd not found in env");
}
