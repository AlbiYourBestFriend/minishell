/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:11:58 by tprovost          #+#    #+#             */
/*   Updated: 2025/02/10 17:17:50 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_quotes(char *cmd)
{
	int		i;
	char	c;

	i = 0;
	while (cmd[i] != '\0')
	{
		if (cmd[i] == "\"" || cmd[i] == '\'')
		{
			c = cmd[i];
			i++;
			while (cmd[i] != c && cmd[i] != '\0')
				i++;
			if (cmd[i] == '\0')
				return (0);
			else
				i++;
		}
		else
			i++;
	}
	return (1);
}
