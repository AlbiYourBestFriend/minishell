/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:18:48 by mleproux          #+#    #+#             */
/*   Updated: 2025/02/11 13:19:39 by mleproux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_token(char *str)
{
	int	token;

	if (str == NULL)
		return (-1);
	token = 0;
	if (ft_strncmp(str, "<", INT_MAX) == 0)
		token = INPUT;
	else if (ft_strncmp(str, "<<", INT_MAX) == 0)
		token = HEREDOC;
	else if (ft_strncmp(str, ">", INT_MAX) == 0)
		token = TRUNC;
	else if (ft_strncmp(str, ">>", INT_MAX) == 0)
		token = APPEND;
	else if (ft_strncmp(str, "|", INT_MAX) == 0)
		token = PIPE;
	return (token);
}