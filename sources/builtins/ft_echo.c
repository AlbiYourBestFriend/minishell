/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:29:38 by mleproux          #+#    #+#             */
/*   Updated: 2025/03/18 11:37:47 by tprovost         ###   ########.fr       */
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
		printf("%s", cmd->args[i]);
		i++;
		if (cmd->args[i] != NULL)
			printf(" ");
	}
	if (new_line == 1)
		printf("\n");
	g_exit_status = 0;
}
