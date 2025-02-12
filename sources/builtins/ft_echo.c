/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:29:38 by mleproux          #+#    #+#             */
/*   Updated: 2025/02/12 16:59:06 by mleproux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_option(t_command *cmd, int *count)
{
	int new_line;
	int	index;

	new_line = 1;
	index = 0;
	while (cmd->args[index])
	{
		if (ft_strncmp(cmd->args[index], "-n", INT_MAX) == 0)
		{
			(*count)++;
			new_line = 0;
		}
		index++;
	}
	return (new_line);
}

void	ft_echo(t_command *cmd)
{
	int	new_line;
	int	index;

	index = 1;
	new_line = check_option(cmd, &index);
	print_output(cmd, index);
	if (new_line)
		write(1, "\n", 1);
}
