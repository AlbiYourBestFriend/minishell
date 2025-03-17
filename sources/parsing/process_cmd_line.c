/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_cmd_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 13:03:50 by tprovost          #+#    #+#             */
/*   Updated: 2025/03/17 12:29:46 by mleproux         ###   ########.fr       */
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
	if (cmd->args == NULL || cmd->args[0] == NULL)
		return (0);
	i = -1;
	while (cmd->args[++i] != NULL)
	{
		tmp = handle_quotes(cmd->args[i]);
		if (tmp == NULL)
			return (0);
		free(cmd->args[i]);
		cmd->args[i] = tmp;
	}
	if (ft_strlen(cmd->args[0]) == 0)
		return (0);
	return (1);
}

