/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:21:31 by mleproux          #+#    #+#             */
/*   Updated: 2025/02/25 14:25:05 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_if_builtins(t_command *cmd)
{
	char	*command_name;

	if (cmd->args == NULL || cmd->args[0] == NULL)
		return (0);
	command_name = cmd->args[0];
	if (ft_strncmp(command_name, "echo", 50) == 0
		|| ft_strncmp(command_name, "cd", 50) == 0
		|| ft_strncmp(command_name, "pwd", 50) == 0
		|| ft_strncmp(command_name, "export", 50) == 0
		|| ft_strncmp(command_name, "unset", 50) == 0
		|| ft_strncmp(command_name, "env", 50) == 0
		|| ft_strncmp(command_name, "exit", 50) == 0)
		return (1);
	return (0);
}

int	execute_builtins(t_data *data, t_command *cmd)
{
	char	*command_name;

	command_name = cmd->args[0];
	if (command_name == NULL)
		return (0);
	if (ft_strncmp(command_name, "echo", 50) == 0)
		ft_echo(cmd);
	else if (ft_strncmp(command_name, "cd", 50) == 0)
		ft_cd(data, cmd);
	else if (ft_strncmp(command_name, "pwd", 50) == 0)
		ft_pwd();
	else if (ft_strncmp(command_name, "export", 50) == 0)
		ft_export(data, cmd);
	else if (ft_strncmp(command_name, "unset", 50) == 0)
		ft_unset(data, cmd);
	else if (ft_strncmp(command_name, "env", 50) == 0)
		ft_env(data, cmd);
	else if (ft_strncmp(command_name, "exit", 50) == 0)
		ft_exit(data, cmd, 1);
	return (0);
}

int	init_builtins(t_data *data, t_command *cmd)
{
	int	output;

	read_redirection(data, cmd);
	if (check_if_builtins(cmd) != 1)
		return (0);
	if (cmd->output_fd != 1)
	{
		output = dup(1);
		dup2(cmd->output_fd, 1);
	}
	execute_builtins(data, cmd);
	if (cmd->output_fd != 1)
	{
		dup2(output, 1);
		close(output);
	}
	return (1);
}
