/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:28:12 by tprovost          #+#    #+#             */
/*   Updated: 2025/03/12 20:12:09 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int	check_path_cd(t_data *data, t_env_var *tmp_env_pwd, char **tab, char *cd_path)
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
			printf("%scd: home/%s%s: No such file or directory\n", \
					ERREUR, data->username, &cd_path[1]); // erreur msg
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

int	cd_check_chdir(char *tmp)
{
	if (tmp[0] == '-' && tmp[1] == '\0')
		return (1);
	if (tmp[0] == '~' && (tmp[1] == '/' || tmp[1] == '\0'))
		return (1);
	if (chdir(tmp) == -1)
		return (0);
	return (1);
}
