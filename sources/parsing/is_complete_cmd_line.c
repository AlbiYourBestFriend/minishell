/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_complete_cmd_line.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 10:47:02 by tprovost          #+#    #+#             */
/*   Updated: 2025/02/24 15:06:59 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_complete_cmd_line(char *cmd)
{
	int	i;

	i = 0;
	if (cmd == NULL)
		return (0);
	while (cmd[i] != '\0')
		i++;
	if (i == 0)
		return (0);
	i--;
	while (ft_isspace(cmd[i]) == 1 && i > 0 && cmd[i] != '|')
		i--;
	if (cmd[i] == '|')
		return (0);
	return (1);
}
