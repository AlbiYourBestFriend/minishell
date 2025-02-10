/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:13:48 by mleproux          #+#    #+#             */
/*   Updated: 2025/02/10 15:09:02 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_data	init_data(char **env)
{
	t_data	data;

	data.commands = NULL;
	data.env = copy_tab(env);
	if (data.env == NULL)
		print_error("Malloc Error");
	return (data);
}
