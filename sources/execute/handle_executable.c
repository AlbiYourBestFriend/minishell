/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_executable.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:55:23 by tprovost          #+#    #+#             */
/*   Updated: 2025/02/21 12:34:29 by tprovost         ###   ########.fr       */
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

void	exec_executable(t_data *data, t_command *cmd)
{
	int			i;
	char		*path;
	char		**tab;
	t_env_var	*tmp;

	try_execute(&cmd->args[0][1], data->env_variables, cmd->args);
	tmp = get_env_var(data, "PWD");
	i = 1;
	if (ft_strlen(tmp->value) - i > 0
		&& tmp->value[ft_strlen(tmp->value) - i] == '/')
	{
		i++;
	}
	path = ft_strjoin(tmp->value, &(cmd->args[0][i]));
	if (access(path, F_OK | X_OK) == 0)
	{
		tab = lst_to_tab(data->env_variables);
		execve(path, cmd->args, tab);
		free_tab(tab);
	}
	free(path);
}
