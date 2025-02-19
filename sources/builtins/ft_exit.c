/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:33:53 by mleproux          #+#    #+#             */
/*   Updated: 2025/02/19 12:03:49 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exit(t_data *data, t_command *cmd)
{
	(void)cmd;
	// je dois gerer si y'a des arguments;
	// stop signaux
	rl_clear_history();
	free_data(data);
	exit(0);
}
