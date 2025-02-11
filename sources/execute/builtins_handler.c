/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:21:31 by mleproux          #+#    #+#             */
/*   Updated: 2025/02/11 17:18:02 by mleproux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_if_builtins(char *command_name)
{
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

int	execute_builtins(char *command_name)
{
	if (command_name == NULL)
		return (0);
	if (ft_strncmp(command_name, "echo", 50) == 0)
		ft_echo(NULL);
	else if (ft_strncmp(command_name, "cd", 50) == 0)
		ft_cd(NULL);
	else if (ft_strncmp(command_name, "pwd", 50) == 0)
		ft_pwd(NULL);
	else if (ft_strncmp(command_name, "export", 50) == 0)
		ft_export(NULL);
	else if (ft_strncmp(command_name, "unset", 50) == 0)
		ft_unset(NULL);
	else if (ft_strncmp(command_name, "env", 50) == 0)
		ft_env(NULL);
	else if (ft_strncmp(command_name, "exit", 50) == 0)
		ft_exit(NULL);
	return (0);
}
