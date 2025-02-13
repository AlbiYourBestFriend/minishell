/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:24:27 by mleproux          #+#    #+#             */
/*   Updated: 2025/02/13 13:08:50 by mleproux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**get_paths(void)
{
	char	**splitted_paths;

	splitted_paths = ft_split(getenv("PATH"), ':');
	return (splitted_paths);
}

char	*create_path(char *path, char *cmd)
{
	char	*temp;
	char	*new_path;

	temp = ft_strjoin(path, "/");
	if (!temp)
		return (NULL);
	new_path = ft_strjoin(temp, cmd);
	free(temp);
	if (!new_path)
		return (NULL);
	return (new_path);
}
