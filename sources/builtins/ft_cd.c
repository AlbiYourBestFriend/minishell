/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:31:02 by mleproux          #+#    #+#             */
/*   Updated: 2025/03/31 15:57:28 by mleproux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	cd_1(t_data *data, t_env_var *tmp_env, char *cd_path);

// join 2 str avec un / entre les 2
static int	cd_3(t_env_var *tmp_env_pwd, char *tab_i)
{
	int		i;
	int		n;
	char	*str;

	i = -1;
	n = 0;
	str = malloc((ft_strlen(tmp_env_pwd->value) + \
					ft_strlen(tab_i) + 2) * sizeof(char));
	if (str == NULL)
		return (allocate_error(ALLOC_ERR), 0);
	while (tmp_env_pwd->value[++i] != '\0')
		str[i] = tmp_env_pwd->value[i];
	str[i] = '/';
	i++;
	while (tab_i[n] != '\0')
	{
		str[i + n] = tab_i[n];
		n++;
	}
	str[i + n] = '\0';
	free(tmp_env_pwd->value);
	tmp_env_pwd->value = str;
	g_exit_status = 0;
	return (1);
}

// tmp_env contient le PWD
// tmp contient l'argument de cd
// tab contient l'argument de cd split au niveau des /
// cd_3 permet de faire des strjoin
static int	cd_2(t_env_var *tmp_env_pwd, char **tab)
{
	int		i;

	if (tab == NULL)
		return (allocate_error(ALLOC_ERR), 0);
	i = 0;
	while (tab[i] != NULL)
	{
		if (ft_strncmp(tab[i], "..", 2) == 0 && ft_strlen(tab[i]) == 2)
			cd_rm_last(tmp_env_pwd->value);
		else if (cd_3(tmp_env_pwd, tab[i]) == 0)
			return (free_tab(tab), 0);
		i++;
	}
	g_exit_status = 0;
	return (free_tab(tab), 1);
}

void	cd_5(t_data *data, t_env_var *tmp_env, char *cd_path)
{
	if (cd_path[0] == '-' && cd_path[1] == '\0')
	{
		if (get_env_var(data, "OLDPWD") != NULL)
		{
			tmp_env = cd_add_pwd(data, "PWD");
			if (tmp_env != NULL)
				cd_1(data, tmp_env, cd_path);
		}
		else
			ft_printf("%scd: OLDPWD not set\n", ERROR);
	}
	else
	{
		tmp_env = cd_add_pwd(data, "PWD");
		if (tmp_env != NULL)
			cd_4(data, tmp_env, ft_strdup(tmp_env->value));
	}
}

// check cd -
// modif PWD
// modif OLDPWD
static void	cd_1(t_data *data, t_env_var *tmp_env, char *cd_path)
{
	char	*pwd;

	if (tmp_env != NULL && tmp_env->value != NULL && tmp_env->value[0] != '\0')
	{
		pwd = ft_strdup(tmp_env->value);
		if (pwd == NULL)
			return (allocate_error(ALLOC_ERR));
		if (count_char(cd_path, '/') == (int)ft_strlen(cd_path))
			return (root_return(data), free(pwd));
		if (cd_path[0] == '-' && cd_path[1] == '\0')
			return (cd_switch_pwd(data, tmp_env), free(pwd));
		if (cd_2(tmp_env, ft_split(cd_path, '/')) == 0)
			return (free(pwd));
		cd_4(data, tmp_env, pwd);
	}
	else
	{
		cd_5(data, tmp_env, cd_path);
	}
}

//	check nb arguments
//	if nb args == 1 => return home/user
//	else : cd_check_chdir
//		trim quotes
//		if chdir ok => chdir + modif PWD
void	ft_cd(t_data *data, t_command *cmd)
{
	char		*cd_path;
	t_env_var	*tmp_env;

	if (tab_len(cmd->args) > 2)
	{
		g_exit_status = 1;
		ft_printf("%s%s: too many arguments\n", ERROR, cmd->args[0]);
	}
	else if (tab_len(cmd->args) == 1)
		return_home_user(data);
	else if (tab_len(cmd->args) == 2)
	{
		cd_path = ft_strtrim(cmd->args[1], "\"\'");
		if (cd_path == NULL)
			allocate_error(ALLOC_ERR);
		else if (cd_check_chdir(cmd, cd_path) == 0)
			return ;
		else
		{
			tmp_env = get_env_var(data, "PWD");
			cd_1(data, tmp_env, cd_path);
			free(cd_path);
		}
	}
}
