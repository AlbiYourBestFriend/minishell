/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:13:48 by mleproux          #+#    #+#             */
/*   Updated: 2025/02/10 18:46:44 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_data	init_data(char **env)
{
	t_data	data;

	data.commands = NULL;
	data.my_env = copy_tab(env);
	if (data.my_env == NULL)
		print_error("Malloc Error");
	data.env_variables = NULL;
	return (data);
}
