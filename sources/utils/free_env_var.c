/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:43:35 by tprovost          #+#    #+#             */
/*   Updated: 2025/02/21 12:27:40 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_env_var(t_env_var *env_var)
{
	if (env_var == NULL)
		return ;
	free(env_var->name);
	free(env_var->value);
	env_var->next = NULL;
	free(env_var);
}
