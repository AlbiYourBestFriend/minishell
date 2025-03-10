/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:31:02 by mleproux          #+#    #+#             */
/*   Updated: 2025/03/10 19:56:13 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	cd_rm_last(char *pwd)
{
	int	i;

	if (ft_strlen(pwd) == 1 && pwd[0] == '/')
		return ;
	if (count_char(pwd, '/') == (int)ft_strlen(pwd))
		return ;
	i = 0;
	while (pwd[i] != '\0')
	{
		i++;
	}
	i--;
	if (pwd[i] == '/')
		i--;
	while (pwd[i] != '/')
	{
		i--;
	}
	if (i != 0)
		pwd[i] = '\0';
	else
		pwd[1] = '\0';
}

static int	cd_utils_utils(t_data *data, t_env_var *tmp_env, char *tmp, char **tab)
{
	int			i;

	if (tab == NULL)
		return (0);
	free(tmp);
	i = -1;
	if (tab[0][0] == '~' && tab[0][1] == '\0')
	{
		return_home_user(data);
		i++;
	}
	while (tab[++i] != NULL)
	{
		if (ft_strncmp(tab[i], "..", 2) == 0 && ft_strlen(tab[i]) == 2)
			cd_rm_last(tmp_env->value);
		else
		{
			tmp = ft_strjoin(tmp_env->value, "/");
			free(tmp_env->value);
			if (tmp == NULL)
				return (free_tab(tab), 0);
			tmp_env->value = tmp;
			tmp = ft_strjoin(tmp_env->value, tab[i]);
			free(tmp_env->value);
			if (tmp == NULL)
				return (free_tab(tab), 0);
			tmp_env->value = tmp;
		}
	}
	return (free_tab(tab), 1);
}

static void	cd_switch_pwd(t_data *data, t_env_var *env_var, char *pwd, char *path)
{
	int			n;
	t_env_var	*tmp_env;

	free(path);
	tmp_env = get_env_var(data, "OLDPWD");
	if (tmp_env == NULL)
		return (free(pwd));
	path = tmp_env->value;
	tmp_env->value = pwd;
	free(env_var->value);
	env_var->value = path;
	n = count_char(env_var->value, '/');
	while (n > 0)
	{
		chdir("..");
		n--;
	}
	chdir(env_var->value);
	printf("%s\n", env_var->value);
}

static void	cd_utils(t_data *data, t_env_var *tmp_env, char *tmp)
{
	char		*pwd;

	pwd = ft_strdup(tmp_env->value);
	if (pwd == NULL)
		return (free(tmp));
	if (tmp[0] == '-' && tmp[1] == '\0')
		return (cd_switch_pwd(data, tmp_env, pwd, tmp));
	if (cd_utils_utils(data, tmp_env, tmp, ft_split(tmp, '/')) == 0)
		return (free(pwd));
	tmp_env = get_env_var(data, "OLDPWD");
	if (tmp_env != NULL)
	{
		if (tmp_env->value != NULL)
			free(tmp_env->value);
		tmp_env->value = pwd;
	}
	else
	{
		free(pwd);
		perror("old pwd not found in env");
	}
}

// check nb arguments
// if nb args == 1 => return home/user
// else : chdir
void	ft_cd(t_data *data, t_command *cmd)
{
	char		*tmp;
	t_env_var	*tmp_env;

	if (tab_len(cmd->args) > 2)
		printf("%s%s: too many arguments\n", ERREUR, cmd->args[0]);
	else if (tab_len(cmd->args) == 1)
		return_home_user(data);
	else if (tab_len(cmd->args) == 2)
	{
		tmp = ft_strtrim(cmd->args[1], "\"\'");
		if (tmp == NULL)
			return ;
		if (((ft_strncmp(tmp, "-", 1) != 0 && ft_strncmp(tmp, "~", 1) != 0)
				|| ft_strlen(tmp) != 1) && chdir(tmp) == -1)
			printf("%s%s: %s: directory not found\n", ERREUR, cmd->args[0], cmd->args[1]);
		else
		{
			tmp_env = get_env_var(data, "PWD");
			if (tmp_env != NULL && tmp_env->value != NULL
				&& tmp_env->value[0] != '\0')
				cd_utils(data, tmp_env, tmp);
			else
				perror("pwd not found or error in env");
		}
	}
}

// refaire tests cas erreur avec cd - et cd ~/...
