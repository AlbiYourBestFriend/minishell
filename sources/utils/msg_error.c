/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:01:53 by mleproux          #+#    #+#             */
/*   Updated: 2025/03/11 12:04:06 by mleproux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	allocate_error(t_data *data, char *err)
{
	data->exit_status = 1;
	printf("%s%s\n", ERREUR, err);
}

void	nofile_error(t_data *data, char *err, char *filename)
{
	data->exit_status = 1;
	printf("%s%s: %s\n", ERREUR, filename, err);
}