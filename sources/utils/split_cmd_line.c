/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 19:03:18 by tprovost          #+#    #+#             */
/*   Updated: 2025/02/04 19:20:39 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**split_cmd_line(char *cmd)
{
	int	i;
	int	n;
	int	c;

	i = 0;
	n = 0;
	while (cmd[i] != '\0')
	{
		c = is_in_str(cmd, i);
		if (c == 0 && is_space(cmd[i]) == 0 && (is_space(cmd[i + 1]) == 1 || cmd[i + 1] == '\0'))
		{
			n++;
		}
		i++;
	}
}
