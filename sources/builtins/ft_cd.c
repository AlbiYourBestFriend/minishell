/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:31:02 by mleproux          #+#    #+#             */
/*   Updated: 2025/03/17 14:31:20 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// join 2 str avec un / entre les 2
static int	cd_utils_3(t_env_var *tmp_env_pwd, char *tab_i)
{
	int		i;
	int		n;
	char	*str;

	i = -1;
	n = -1;
	str = malloc((ft_strlen(tmp_env_pwd->value) + \
					ft_strlen(tab_i) + 2) * sizeof(char));
	if (str == NULL)
		return (allocate_error(ALLOC_ERR), 0);
	while (tmp_env_pwd->value[++i] != '\0')
		str[i] = tmp_env_pwd->value[i];
	str[i] = '/';
	i++;
	while (tab_i[++n] != '\0')
		str[i + n] = tab_i[n];
	str[i + n] = '\0';
	free(tmp_env_pwd->value);
	tmp_env_pwd->value = str;
	return (1);
}

// tmp_env contient le PWD
// tmp contient l'argument de cd
// tab contient l'argument de cd split au niveau des /
// cd_utils_3 permet de faire des strjoin
static int	cd_utils_2(t_data *data, t_env_var *tmp_env_pwd, \
						char *cd_path, char **tab)
{
	int		i;

	if (tab == NULL)
		return (allocate_error(ALLOC_ERR), 0);
	i = -1;
	if (tab[0][0] == '~' && tab[0][1] == '\0')
	{
		if (check_path_cd(data, tmp_env_pwd, tab, cd_path) == 0)
			return (free_tab(tab), 0);
		i++;
	}
	while (tab[++i] != NULL)
	{
		if (ft_strncmp(tab[i], "..", 2) == 0 && ft_strlen(tab[i]) == 2)
			cd_rm_last(tmp_env_pwd->value);
		else if (cd_utils_3(tmp_env_pwd, tab[i]) == 0)
			return (free_tab(tab), 0);
	}
	return (free_tab(tab), 1);
}

// handle cd -
static void	cd_switch_pwd(t_data *data, t_env_var *env_var_pwd)
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
	printf("%s\n", env_var_pwd->value);
}

// check cd -
// modif PWD
// modif OLDPWD
static void	cd_utils(t_data *data, t_env_var *tmp_env, char *cd_path)
{
	char	*pwd;

	if (tmp_env != NULL && tmp_env->value != NULL && tmp_env->value[0] != '\0')
	{
		pwd = ft_strdup(tmp_env->value);
		if (pwd == NULL)
			return (allocate_error(ALLOC_ERR));
		if (cd_path[0] == '/' && cd_path[1] == '\0')
			return (root_return(data));
		if (cd_path[0] == '-' && cd_path[1] == '\0')
			return (cd_switch_pwd(data, tmp_env), free(pwd));
		if (cd_utils_2(data, tmp_env, cd_path, ft_split(cd_path, '/')) == 0)
			return (free(pwd));
		tmp_env = get_env_var(data, "OLDPWD");
		if (tmp_env != NULL)
		{
			if (tmp_env->value != NULL)
				free(tmp_env->value);
			tmp_env->value = pwd;
		}
		else
			return (free(pwd), perror("old pwd not found in env"));
	}
	else
		perror("pwd not found in env");
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
		printf("%s%s: too many arguments\n", ERROR, cmd->args[0]);
	}
	else if (tab_len(cmd->args) == 1)
		return_home_user(data);
	else if (tab_len(cmd->args) == 2)
	{
		cd_path = ft_strtrim(cmd->args[1], "\"\'");
		if (cd_path == NULL)
			allocate_error(ALLOC_ERR);
		else if (cd_check_chdir(cd_path) == 0)
			printf("%scd: %s: %s\n", ERROR, cmd->args[1], NO_FILE_DIR);
		else
		{
			tmp_env = get_env_var(data, "PWD");
			cd_utils(data, tmp_env, cd_path);
			free(cd_path);
		}
	}
}
