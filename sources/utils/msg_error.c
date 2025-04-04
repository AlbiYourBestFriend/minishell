/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:01:53 by mleproux          #+#    #+#             */
/*   Updated: 2025/04/02 16:58:33 by mleproux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	allocate_error(char *err)
{
	g_exit_status = 1;
	ft_printf("%s%s\n", ERROR, err);
}

void	nofile_error(char *err, char *filename)
{
	g_exit_status = 1;
	ft_printf("%s%s: %s\n", ERROR, filename, err);
}

void	noperm_error(char *err, char *filename)
{
	g_exit_status = 126;
	ft_printf("%s%s: %s\n", ERROR, filename, err);
}
