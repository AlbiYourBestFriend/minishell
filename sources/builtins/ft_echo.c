/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:29:38 by mleproux          #+#    #+#             */
/*   Updated: 2025/02/21 16:31:25 by mleproux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_echo(t_command *cmd)
{
	int	i;
	int	new_line;

	i = 1;
	new_line = 1;
	while (ft_strncmp(cmd->args[i], "-n", INT_MAX) == 0)
	{
		new_line = 0;
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
}
