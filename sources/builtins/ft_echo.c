/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:29:38 by mleproux          #+#    #+#             */
/*   Updated: 2025/02/13 18:02:09 by mleproux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_option(t_command *cmd, int *count)
{
	int	new_line;
	int	i;

	new_line = 1;
	i = 0;
	while (cmd->args[i])
	{
		if (ft_strncmp(cmd->args[i], "-n", INT_MAX) == 0)
		{
			(*count)++;
			new_line = 0;
		}
		i++;
	}
	return (new_line);
}

void	ft_echo(t_data *data, t_command *cmd)
{
	int	new_line;
	int	i;

	i = 1;
	new_line = check_option(cmd, &i);
	print_output(cmd, i);
	if (new_line)
		write(1, "\n", 1);
	ft_exit(data, NULL);
}
