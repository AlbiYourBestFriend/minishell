/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:28:12 by tprovost          #+#    #+#             */
/*   Updated: 2025/03/11 21:28:21 by tprovost         ###   ########.fr       */
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

int	return_home_user(t_data *data)
{
	int			n;
	t_env_var	*tmp;

	tmp = get_env_var(data, "PWD");
	if (tmp == NULL)
		return (0);
	n = count_char(tmp->value, '/');
	while (n > 0)
	{
		chdir("..");
		n--;
	}
	if (access("home", F_OK | X_OK) == 0)
	{
		chdir("home");
		if (access(data->username, F_OK | X_OK) == 0)
			return (chdir(data->username), 1);
		else
			chdir("..");
	}
	return (0);
}

int	check_path_cd(t_data *data, t_env_var *tmp_env_pwd, char **tab)
{
	int	i;

	i = 1;
	if (return_home_user(data) == 0)
		return (0);
	while (tab[i] != NULL)
	{
		if (access(tab[i], F_OK | X_OK) == 0)
			chdir(tab[i]);
		else
		{
			while (i >= 0)
			{
				chdir("..");
				i--;
			}
			chdir(tmp_env_pwd->value);
			return (0);
		}
		i++;
	}
	return (1);
}

int cd_check_chdir(char *tmp)
{
	if (tmp[0] == '-' && tmp[1] == '\0')
		return (1);
	if (tmp[0] == '~' && (tmp[1] == '/' || tmp[1] == '\0'))
		return (1);
	if (chdir(tmp) == -1)
		return (0);
	return (1);
}
