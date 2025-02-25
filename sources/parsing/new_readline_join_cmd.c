/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_readline_join_cmd.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 10:44:28 by tprovost          #+#    #+#             */
/*   Updated: 2025/02/25 16:12:56 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*new_readline_join_cmd(t_data *data, char *cmd)
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
	data->count_line++;
	str = ft_strjoin(cmd, " ");
	free(cmd);
	if (str == NULL)
		return (NULL);
	cmd = str;
	str = ft_strjoin(cmd, tmp);
	free(cmd);
	free(tmp);
	if (str == NULL)
		return (NULL);
	cmd = str;
	return (cmd);
}
