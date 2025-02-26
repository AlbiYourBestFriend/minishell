/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_executable.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:55:23 by tprovost          #+#    #+#             */
/*   Updated: 2025/02/26 12:48:34 by tprovost         ###   ########.fr       */
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
	{
		perror("Malloc error");
		free_data(data);
		rl_clear_history();
		exit(1);
	}
	if (access(path, F_OK | X_OK) == 0)
	{
		tab = lst_to_tab(data->env_variables);
		execve(path, cmd->args, tab);
		free_tab(tab);
	}
	free(path);
}

void	exec_executable(t_data *data, t_command *cmd)
{
	t_env_var	*tmp;

	if (try_execute(&cmd->args[0][1], \
	data->env_variables, cmd->args, data) == 0)
	{
		free_data(data);
		rl_clear_history();
		exit(1);
	}
	tmp = get_env_var(data, "PWD");
	if (tmp == NULL)
	{
		printf("pwd not found\n");
		free_data(data);
		rl_clear_history();
		exit(1);
	}
	exec_executable_utils(data, cmd, tmp);
	perror(cmd->args[0]);
	free_data(data);
	rl_clear_history();
	exit(1);
}
