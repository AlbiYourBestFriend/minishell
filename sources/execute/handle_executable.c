/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_executable.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:55:23 by tprovost          #+#    #+#             */
/*   Updated: 2025/02/21 14:12:44 by mleproux         ###   ########.fr       */
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

void	exec_executable(t_env_var *env_var, t_command *cmd, t_data *data)
{
	int			i;
	char		*path;
	char		**tab;
	t_env_var	*tmp;

	try_execute(&cmd->args[0][1], env_var, cmd->args, data);
	tmp = env_var;
	while (tmp != NULL && (ft_strncmp(tmp->name, "PWD", 3) != 0
			|| ft_strlen(tmp->name) != 3))
		tmp = tmp->next;
	i = 1;
	if (ft_strlen(tmp->value) - i > 0
		&& tmp->value[ft_strlen(tmp->value) - i] == '/')
	{
		i++;
	}
	path = ft_strjoin(tmp->value, &(cmd->args[0][i]));
	if (access(path, F_OK | X_OK) == 0)
	{
		tab = lst_to_tab(env_var);
		execve(path, cmd->args, tab);
		free_tab(tab);
	}
	free(path);
}
