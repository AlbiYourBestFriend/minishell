/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:28:12 by tprovost          #+#    #+#             */
/*   Updated: 2025/03/18 14:14:46 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env_var	*cd_add_pwd(t_data *data, char *name)
{
	char	pwd[MY_CHAR_MAX];

	if (getcwd(pwd, MY_CHAR_MAX) == NULL)
	{
		return (NULL);
	}
	return (add_env_var(data, ft_strdup(name), ft_strdup(pwd)));
}

// handle cd ..
void	cd_rm_last(char *pwd)
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

// check si le chemin d'acces existe et peut etre accede
// si oui on y va
// sinon ERROR
int	check_path_cd(t_data *data, t_env_var *tmp_env_pwd, \
					char **tab, char *cd_path)
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
			printf("%scd: home/%s%s: %s\n", \
					ERROR, data->username, &cd_path[1], NO_FILE_DIR);
			while (i >= 0)
			{
				chdir("..");
				i--;
			}
			chdir(tmp_env_pwd->value);
			g_exit_status = 1;
			return (0);
		}
		i++;
	}
	return (1);
}

int	cd_check_chdir(t_command *cmd, char *cd_path)
{
	if (cd_path[0] == '-' && cd_path[1] == '\0')
		return (1);
	if (cd_path[0] == '~' && (cd_path[1] == '/' || cd_path[1] == '\0'))
		return (1);
	if (chdir(cd_path) == -1)
	{
		g_exit_status = 1;
		if (access(cd_path, F_OK) == 0)
			printf("%scd: %s: %s\n", ERROR, cmd->args[1], NO_DIR);
		else
			printf("%scd: %s: %s\n", ERROR, cmd->args[1], NO_FILE_DIR);
		free(cd_path);
		return (0);
	}
	return (1);
}
