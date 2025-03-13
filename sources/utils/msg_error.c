/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:01:53 by mleproux          #+#    #+#             */
/*   Updated: 2025/03/13 11:44:39 by mleproux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	allocate_error(char *err)
{
	g_exit_status = 1;
	printf("%s%s\n", ERREUR, err);
}

void	nofile_error(char *err, char *filename)
{
	g_exit_status = 1;
	printf("%s%s: %s\n", ERREUR, filename, err);
}
