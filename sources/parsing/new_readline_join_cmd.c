/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_readline_join_cmd.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 10:44:28 by tprovost          #+#    #+#             */
/*   Updated: 2025/02/24 15:07:11 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*new_readline_join_cmd(char *cmd)
{
	char	*str;
	char	*tmp;

	str = NULL;
	tmp = readline("> ");
	if (tmp == NULL)
	{
		free(cmd);
		return (NULL);
	}
	str = ft_strjoin(cmd, " ");
	free(cmd);
	cmd = str;
	str = ft_strjoin(cmd, tmp);
	free(cmd);
	free(tmp);
	cmd = str;
	return (cmd);
}
