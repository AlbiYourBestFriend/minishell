/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:18:48 by mleproux          #+#    #+#             */
/*   Updated: 2025/02/24 15:52:25 by mleproux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_token(char *cmd_line, int i)
{
	if (cmd_line[i] == '<')
	{
		if (cmd_line[i + 1] == '<')
			return (2);
		return (1);
	}
	else if (cmd_line[i] == '>')
	{
		if (cmd_line[i + 1] == '>')
			return (4);
		return (3);
	}
	return (0);
}
