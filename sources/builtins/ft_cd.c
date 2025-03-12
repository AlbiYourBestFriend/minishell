/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:31:02 by mleproux          #+#    #+#             */
/*   Updated: 2025/02/27 16:22:38 by tprovost         ###   ########.fr       */
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

static int	cd_utils_utils(t_env_var *tmp_env, char *tmp, char **tab)
{
	int			i;

	if (tab == NULL)
		return (0);
	free(tmp);
	i = -1;
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

static void	cd_utils(t_data *data, t_env_var *tmp_env, char *tmp)
{
	char		*pwd;

	pwd = ft_strdup(tmp_env->value);
	if (pwd == NULL)
		return (free(tmp));
	if (cd_utils_utils(tmp_env, tmp, ft_split(tmp, '/')) == 0)
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

void	ft_cd(t_data *data, t_command *cmd)
{
	char		*tmp;
	t_env_var	*tmp_env;

	if (tab_len(cmd->args) > 2)
		printf("%s%s: too many arguments\n", ERREUR, cmd->args[0]);
	else if (tab_len(cmd->args) == 1)
		root_return(data);
	else if (tab_len(cmd->args) == 2)
	{
		tmp = ft_strtrim(cmd->args[1], "\"\'");
		if (tmp == NULL)
			return ;
		if (chdir(tmp) == -1)
			printf("%s%s: directory not found", ERREUR, cmd->args[0]);
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
