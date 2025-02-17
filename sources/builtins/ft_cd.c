/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:31:02 by mleproux          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/02/17 16:27:59 by tprovost         ###   ########.fr       */
=======
/*   Updated: 2025/02/17 15:07:46 by mleproux         ###   ########.fr       */
>>>>>>> refs/remotes/origin/main
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	root_return(t_data *data)
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
	else
		perror("pwd not found in env");
}

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

void	ft_cd(t_data *data, t_command *cmd)
{
	int			result;
	int			i;
	char		*pwd;
	char		*tmp;
	char		**tab;
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
			if (tmp_env != NULL && tmp_env->value != NULL && tmp_env->value[0] != '\0')
			{
				pwd = ft_strdup(tmp_env->value);
				tab = ft_split(tmp, '/');
				free(tmp);
				i = 0;
				while (tab[i] != NULL)
				{
					if (ft_strncmp(tab[i], "..", 2)	== 0 && ft_strlen(tab[i]) == 2)
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
	}
	// ft_exit(data, NULL);
}
