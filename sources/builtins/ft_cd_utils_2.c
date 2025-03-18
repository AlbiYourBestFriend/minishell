/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:22:24 by tprovost          #+#    #+#             */
/*   Updated: 2025/03/18 11:50:45 by tprovost         ###   ########.fr       */
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

// retourne a la racine
// modifie PWD et OLDPWD
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
			return (allocate_error(ALLOC_ERR));
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
	g_exit_status = 0;
}

// handle cd et cd ~
// va a /home/username
int	return_home_user(t_data *data)
{
	g_exit_status = 0;
	root_return(data);
	if (g_exit_status == 1)
	{
		return (0);
	}
	if (access("home", F_OK | X_OK) == 0)
	{
		chdir("home");
		if (access(data->username, F_OK | X_OK) == 0)
			return (chdir(data->username), 1);
		else
			chdir("..");
	}
	g_exit_status = 1;
	return (0);
}
