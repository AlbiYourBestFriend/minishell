/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:08:49 by mleproux          #+#    #+#             */
/*   Updated: 2025/02/18 17:05:04 by mleproux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	open_file(char *filename, int currentfd, int isoutput, int dotrunc)
{
	int	fd;

	if (currentfd > 1)
		close(currentfd);
	if (isoutput == 1)
	{
		if (dotrunc)
			fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	else
		fd = open(filename, O_RDONLY);
	if (fd == -1)
		perror(filename);
	return (fd);
}
