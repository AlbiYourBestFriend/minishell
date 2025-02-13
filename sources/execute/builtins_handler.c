/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:21:31 by mleproux          #+#    #+#             */
/*   Updated: 2025/02/13 14:04:49 by mleproux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_if_builtins(t_command *cmd)
{
	char	*command_name;

	command_name = cmd->args[0];
	if (command_name == NULL)
		return (0);
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

int	execute_builtins(t_command *cmd)
{
	char	*command_name;

	command_name = cmd->args[0];
	if (ft_strncmp(command_name, "echo", 50) == 0)
		ft_echo(cmd);
	else if (ft_strncmp(command_name, "cd", 50) == 0)
		ft_cd(cmd);
	else if (ft_strncmp(command_name, "pwd", 50) == 0)
		ft_pwd();
	else if (ft_strncmp(command_name, "export", 50) == 0)
		ft_export();
	else if (ft_strncmp(command_name, "unset", 50) == 0)
		ft_unset();
	else if (ft_strncmp(command_name, "env", 50) == 0)
		ft_env();
	else if (ft_strncmp(command_name, "exit", 50) == 0)
		ft_exit();
	return (0);
}
