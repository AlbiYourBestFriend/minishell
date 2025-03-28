/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:01:53 by mleproux          #+#    #+#             */
/*   Updated: 2025/03/28 11:51:03 by tprovost         ###   ########.fr       */
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
