/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:29:38 by mleproux          #+#    #+#             */
/*   Updated: 2025/03/20 16:16:20 by mleproux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_parameter(char *arg)
{
	int	index;

	index = 1;
	while (arg[index] != '\0')
	{
		if (arg[index] != 'n')
			return (0);
		index++;
	}
	return (1);
}

void	ft_echo(t_command *cmd)
{
	int	i;
	int	new_line;

	i = 1;
	new_line = 1;
	while (cmd->args[i])
	{
		if (cmd->args[i][0] == '-' && get_parameter(cmd->args[i]) == 1)
			new_line = 0;
		else
			break ;
		i++;
	}
	while (cmd->args[i] != NULL)
	{
		ft_putstr_fd(cmd->args[i], 1);
		i++;
		if (cmd->args[i] != NULL)
			printf(" ");
	}
	if (new_line == 1)
		ft_putstr_fd("\n", 1);
	g_exit_status = 0;
}
