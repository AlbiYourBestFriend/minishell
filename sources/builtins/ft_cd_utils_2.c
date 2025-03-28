/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:22:24 by tprovost          #+#    #+#             */
/*   Updated: 2025/03/28 12:14:02 by mleproux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	root_return_utils(t_data *data, t_env_var *tmp, char *pwd)
{
	char	*name;

	tmp->value[0] = '/';
	tmp->value[1] = '\0';
	tmp = get_env_var(data, "OLDPWD");
	if (tmp != NULL)
	{
		if (tmp->value != NULL)
			free(tmp->value);
		tmp->value = pwd;
	}
	else
	{
		name = ft_strdup("OLDPWD");
		if (name == NULL)
			return (allocate_error(ALLOC_ERR));
		if (add_env_var(data, name, pwd) == NULL)
		{
			free(name);
			free(pwd);
		}
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
			return (allocate_error(ALLOC_ERR));
		n = -1;
		while (++n < count_char(pwd, '/'))
		{
			chdir("..");
		}
		root_return_utils(data, tmp, pwd);
	}
	else if (cd_add_pwd(data, "PWD") != NULL)
		root_return(data);
	else
	{
		g_exit_status = 1;
		return ;
	}
	g_exit_status = 0;
}

void	return_home_user(t_data *data)
{
	t_env_var	*tmp;

	g_exit_status = 0;
	root_return(data);
	if (g_exit_status == 1)
		return ;
	tmp = get_env_var(data, "HOME");
	if (tmp == NULL)
	{
		ft_printf("%scd: HOME not set\n", ERROR);
		g_exit_status = 1;
		return ;
	}
	if (tmp->value == NULL)
		return ;
	if (access(tmp->value, F_OK | X_OK) == 0)
	{
		chdir(tmp->value);
	}
	else
		g_exit_status = 1;
	return ;
}

// handle cd -
void	cd_switch_pwd(t_data *data, t_env_var *env_var_pwd)
{
	int			n;
	char		*pwd;
	t_env_var	*tmp_env_old_pwd;

	tmp_env_old_pwd = get_env_var(data, "OLDPWD");
	if (tmp_env_old_pwd == NULL)
		return ;
	pwd = env_var_pwd->value;
	env_var_pwd->value = tmp_env_old_pwd->value;
	tmp_env_old_pwd->value = pwd;
	n = count_char(env_var_pwd->value, '/');
	while (n > 0)
	{
		chdir("..");
		n--;
	}
	chdir(env_var_pwd->value);
	ft_printf("%s\n", env_var_pwd->value);
	g_exit_status = 0;
}
