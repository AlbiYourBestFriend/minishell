/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:21:31 by mleproux          #+#    #+#             */
/*   Updated: 2025/02/17 12:41:10 by mleproux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_if_builtins(t_command *cmd)
{
	char	*command_name;

	command_name = cmd->args[0];
	if (command_name == NULL)
		return (0);
	if (ft_strncmp(command_name, ECHO, 50) == 0
		|| ft_strncmp(command_name, CD, 50) == 0
		|| ft_strncmp(command_name, PWD, 50) == 0
		|| ft_strncmp(command_name, EXPORT, 50) == 0
		|| ft_strncmp(command_name, UNSET, 50) == 0
		|| ft_strncmp(command_name, ENV, 50) == 0
		|| ft_strncmp(command_name, EXIT, 50) == 0)
		return (1);
	return (0);
}

int	execute_builtins(t_data *data, t_command *cmd)
{
	char	*command_name;

	command_name = cmd->args[0];
	if (command_name == NULL)
		return (0);
	if (ft_strncmp(command_name, ECHO, 50) == 0)
		ft_echo(data, cmd);
	else if (ft_strncmp(command_name, CD, 50) == 0)
		ft_cd(data, cmd);
	else if (ft_strncmp(command_name, PWD, 50) == 0)
		ft_pwd(data);
	else if (ft_strncmp(command_name, EXPORT, 50) == 0)
		ft_export(data, cmd);
	else if (ft_strncmp(command_name, UNSET, 50) == 0)
		ft_unset(data, cmd);
	else if (ft_strncmp(command_name, ENV, 50) == 0)
		ft_env(data, cmd);
	else if (ft_strncmp(command_name, EXIT, 50) == 0)
		ft_exit(data, cmd);
	return (0);
}

int	init_builtins(t_data *data, t_command *cmd)
{
	int	output;

	if (cmd->output_fd > 0)
	{
		output = dup(1);
		dup2(cmd->output_fd, 1);
	}
	execute_builtins(data, cmd);
	if (cmd->output_fd > 0)
	{
		dup2(1, output);
		close(output);
	}
	return (1);
}
