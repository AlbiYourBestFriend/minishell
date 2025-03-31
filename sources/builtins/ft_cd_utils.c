/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:28:12 by tprovost          #+#    #+#             */
/*   Updated: 2025/03/31 15:55:45 by mleproux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env_var	*cd_add_pwd(t_data *data, char *name)
{
	char		pwd[MY_CHAR_MAX];
	char		*new_name;
	char		*new_pwd;
	t_env_var	*tmp;

	if (getcwd(pwd, MY_CHAR_MAX) == NULL)
		return (NULL);
	if (exist_var(data, "PWD") == 1)
	{
		tmp = get_env_var(data, "PWD");
		if (tmp->value != NULL)
			free(tmp->value);
		tmp->value = pwd;
		return (tmp);
	}
	new_name = ft_strdup(name);
	if (new_name == NULL)
		return (NULL);
	new_pwd = ft_strdup(pwd);
	if (new_pwd == NULL)
		return (free(new_name), NULL);
	return (add_env_var(data, new_name, new_pwd));
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

int	cd_check_chdir(t_command *cmd, char *cd_path)
{
	if (cd_path[0] == '-' && cd_path[1] == '\0')
		return (1);
	if (chdir(cd_path) == -1)
	{
		g_exit_status = 1;
		if (access(cd_path, F_OK) == 0)
		{
			if (access(cd_path, X_OK) != 0)
				ft_printf("%scd: %s: %s\n", ERROR, cmd->args[1], NO_PERM);
			else
				ft_printf("%scd: %s: %s\n", ERROR, cmd->args[1], NO_DIR);
		}
		else
			ft_printf("%scd: %s: %s\n", ERROR, cmd->args[1], NO_FILE_DIR);
		free(cd_path);
		return (0);
	}
	return (1);
}
