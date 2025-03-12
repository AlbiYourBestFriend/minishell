/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_cmd_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 13:03:50 by tprovost          #+#    #+#             */
/*   Updated: 2025/03/11 10:57:53 by mleproux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	process_cmd_line(t_data *data, t_command *cmd)
{
	int		i;
	char	*tmp;

	if (read_redirection(data, cmd) == 0)
		return (0);
	tmp = handle_dollars(data, cmd->cmd_line);
	if (tmp == NULL)
		return (0);
	free(cmd->cmd_line);
	cmd->cmd_line = tmp;
	cmd->args = split_cmd_line(cmd->cmd_line, ' ');
	if (cmd->args == NULL)
		return (0);
	i = 0;
	while (cmd->args[i] != NULL)
	{
		tmp = handle_quotes(data, cmd->args[i]);
		if (tmp == NULL)
			return (0);
		free(cmd->args[i]);
		cmd->args[i] = tmp;
		i++;
	}
	return (1);
}
