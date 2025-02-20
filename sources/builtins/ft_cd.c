/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:31:02 by mleproux          #+#    #+#             */
/*   Updated: 2025/02/19 15:52:18 by tprovost         ###   ########.fr       */
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

static void	cd_utils_utils(t_env_var *tmp_env, char *tmp)
{
	int			i;
	char		**tab;

	tab = ft_split(tmp, '/');
	free(tmp);
	i = 0;
	while (tab[i] != NULL)
	{
		if (ft_strncmp(tab[i], "..", 2) == 0 && ft_strlen(tab[i]) == 2)
			cd_rm_last(tmp_env->value);
		else
		{
			tmp = ft_strjoin(tmp_env->value, "/");
			free(tmp_env->value);
			tmp_env->value = tmp;
			tmp = ft_strjoin(tmp_env->value, tab[i]);
			free(tmp_env->value);
			tmp_env->value = tmp;
		}
		i++;
	}
	free_tab(tab);
}

static void	cd_utils(t_data *data, t_env_var *tmp_env, char *tmp)
{
	char		*pwd;

	if (tmp_env != NULL && tmp_env->value != NULL && tmp_env->value[0] != '\0')
	{
		pwd = ft_strdup(tmp_env->value);
		cd_utils_utils(tmp_env, tmp);
		tmp_env = data->env_variables;
		while (tmp_env != NULL && (ft_strlen(tmp_env->name) != 6
				|| ft_strncmp(tmp_env->name, "OLDPWD", 6) != 0))
			tmp_env = tmp_env->next;
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
	else
		perror("pwd not found or error in env");
}

void	ft_cd(t_data *data, t_command *cmd)
{
	int			result;
	char		*tmp;
	t_env_var	*tmp_env;

	if (tab_len(cmd->args) > 2)
		perror("too many arguments");
	else if (tab_len(cmd->args) == 1)
		root_return(data);
	else if (tab_len(cmd->args) == 2)
	{
		tmp = ft_strtrim(cmd->args[1], "\"\'");
		result = chdir(tmp);
		if (result == -1)
			perror("directory not found");
		else
		{
			tmp_env = data->env_variables;
			while (tmp_env != NULL && (ft_strncmp(tmp_env->name, "PWD", 3) != 0
					|| ft_strlen(tmp_env->name) != 3))
				tmp_env = tmp_env->next;
			cd_utils(data, tmp_env, tmp);
		}
	}
}
