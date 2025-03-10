/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:28:12 by tprovost          #+#    #+#             */
/*   Updated: 2025/03/10 18:51:00 by tprovost         ###   ########.fr       */
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
		return_home_user_utils(tmp, pwd);
	}
	else
		perror("pwd not found in env");
}

void	return_home_user(t_data *data)
{
	int			n;
	t_env_var	*tmp;

	tmp = get_env_var(data, "PWD");
	if (tmp == NULL)
		return ;
	n = count_char(tmp->value, '/');
	while (n > 0)
	{
		chdir("..");
		n--;
	}
	if (access("home", F_OK) == 0)
	{
		if (access(data->username, F_OK) == 0)
		{
			chdir("home");
			chdir(data->username);
		}
	}
}
