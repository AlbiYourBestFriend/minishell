/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:41:43 by tprovost          #+#    #+#             */
/*   Updated: 2025/02/12 16:43:22 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_cmd(t_command *cmd)
{
	free(cmd->cmd_line);
	free_tab(cmd->args);
	cmd->next = NULL;
	free(cmd);
}
