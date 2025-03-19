/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_executable.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:55:23 by tprovost          #+#    #+#             */
/*   Updated: 2025/03/19 10:05:01 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_executable(char *cmd)
{
	if (cmd == NULL)
		return (0);
	if (cmd[0] != '.')
		return (0);
	if (cmd[1] != '/')
		return (0);
	if (cmd[2] <= 32 || cmd[2] >= 127)
		return (0);
	return (1);
}

static void	exec_executable_utils(t_data *data, t_command *cmd, t_env_var *tmp)
{
	int		i;
	char	*path;
	char	**tab;

	i = 1;
	if (ft_strlen(tmp->value) - i > 0
		&& tmp->value[ft_strlen(tmp->value) - i] == '/')
		i++;
	path = ft_strjoin(tmp->value, &(cmd->args[0][i]));
	if (path == NULL)
		return (allocate_error(ALLOC_ERR), free_all_exit(data, g_exit_status));
	if (access(path, F_OK) == 0)
	{
		if (access(path, X_OK) == -1)
			return (free(path), nofile_error(NO_PERM, cmd->args[0]), \
				free_all_exit(data, 126));
		tab = lst_to_tab(data->env_variables);
		if (tab == NULL)
			return (free(path), allocate_error(ALLOC_ERR), \
				free_all_exit(data, g_exit_status));
		execve(path, cmd->args, tab);
		free_tab(tab);
	}
	free(path);
	g_exit_status = 127;
}

void	exec_executable(t_data *data, t_command *cmd)
{
	t_env_var	*tmp;

	if (try_execute(&cmd->args[0][1], \
	data->env_variables, cmd->args, 0) == 0)
	{
		free_all_exit(data, g_exit_status);
	}
	tmp = get_env_var(data, "PWD");
	if (tmp == NULL)
	{
		printf("pwd not found\n");
		free_all_exit(data, g_exit_status);
	}
	exec_executable_utils(data, cmd, tmp);
	free_all_exit(data, g_exit_status);
}
