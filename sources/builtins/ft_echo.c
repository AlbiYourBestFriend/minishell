/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:29:38 by mleproux          #+#    #+#             */
/*   Updated: 2025/02/20 18:17:01 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_echo(t_data *data, t_command *cmd)
{
	int	n;

	n = 1;
	if (tab_len(cmd->args) > 1)
	{
		while (ft_strncmp(cmd->args[n], "-n", 2) == 0
			&& ft_strlen(cmd->args[n]) == 2)
		{
			n++;
		}
		print_output(data, cmd, n);
		if (n == 1)
			write(1, "\n", 1);
	}
}
