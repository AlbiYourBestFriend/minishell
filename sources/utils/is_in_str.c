/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_in_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:08:52 by mleproux          #+#    #+#             */
/*   Updated: 2025/02/06 13:11:40 by mleproux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int isquote(char c)
{
	
}

int	is_in_str(char *cmd, int i)
{
	int	j;
	int	c1;
	int	c2;

	j = 0;
	c1 = 0;
	c2 = 0;
	while (j <= i)
	{
		if (cmd[j] == '\"' && cmd[j - 1] != '\\' && c1 == 0)
			c1 = 1;
		else if (cmd[j] == '\'' && cmd[j - 1] != '\\' && c2 == 0)
			c2 = 1;
		else if (cmd[j - 1] == '\"' && cmd[j - 2] != '\\' && c2 == 0 && c1 == 1)
			c1 = 0;
		else if (cmd[j - 1] == '\'' && cmd[j - 2] != '\\' && c1 == 0 && c2 == 1)
			c2 = 0;
		j++;
	}
	if (c1 == 1 || c2 == 1)
		return (1);
	return (0);
}
