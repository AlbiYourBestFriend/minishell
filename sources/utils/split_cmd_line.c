/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 19:03:18 by tprovost          #+#    #+#             */
/*   Updated: 2025/02/05 14:13:46 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**split_cmd_line(char *cmd)
{
	int		i;
	int		j;
	int		n;
	int		c;
	char	**tab;

	i = 0;
	n = 0;
	while (cmd[i] != '\0')
	{
		c = is_in_str(cmd, i);
		if (c == 0 && ft_isspace(cmd[i]) == 0 && (ft_isspace(cmd[i + 1]) == 1 || cmd[i + 1] == '\0'))
			n++;
		i++;
	}
	tab = malloc ((n + 1) * sizeof(char *));
	i = 0;
	while (cmd[i] != '\0')
	{
		j = i;
		while (cmd[i] != '\0' && ft_isspace(cmd[i]) == 0)
			i++;
		if (cmd[i] != '\0')
			i++;
	}
}
