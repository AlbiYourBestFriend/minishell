/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:24:27 by mleproux          #+#    #+#             */
/*   Updated: 2025/02/21 12:34:29 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*create_path(char *path, char *cmd)
{
	char	*temp;
	char	*new_path;

	temp = ft_strjoin(path, "/");
	if (temp == NULL)
		return (NULL);
	new_path = ft_strjoin(temp, cmd);
	free(temp);
	if (new_path == NULL)
		return (NULL);
	return (new_path);
}
