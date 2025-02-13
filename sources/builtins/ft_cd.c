/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:31:02 by mleproux          #+#    #+#             */
/*   Updated: 2025/02/13 16:50:56 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_cd(t_command *cmd)
{
	int	result;

	if (tab_len(cmd->args) > 2)
		printf("trop d'arguments");
	result = chdir(cmd->args[1]);
	if (result == -1)
		printf("erreur");
}
