/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:01:53 by mleproux          #+#    #+#             */
/*   Updated: 2025/03/12 17:19:54 by tprovost         ###   ########.fr       */
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
