/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:44:32 by mleproux          #+#    #+#             */
/*   Updated: 2025/02/13 15:23:33 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_here_doc(int fd, char *limiter)
{
	char	*buffer;

	buffer = NULL;
	while (1)
	{
		buffer = readline(">");
		if (buffer == NULL)
			return (0);
		else if ((ft_strncmp(buffer, limiter, INT_MAX) == 0))
			break ;
		ft_putstr_fd(buffer, fd);
		free(buffer);
	}
	free(buffer);
	close(fd);
	return (1);
}

int	here_doc(int currentfd, char *limiter)
{
	int	fd;

	if (currentfd > 0)
		close(currentfd);
	fd = open(HEREDOCFILE, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (fd);
	if (get_here_doc(fd, limiter) == 0)
	{
		unlink(HEREDOCFILE);
		return (-1);
	}
	fd = open(HEREDOCFILE, O_RDONLY);
	if (fd < 0)
		unlink(HEREDOCFILE);
	return (fd);
}
