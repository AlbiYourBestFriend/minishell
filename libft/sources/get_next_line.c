/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 10:08:00 by mleproux          #+#    #+#             */
/*   Updated: 2025/01/14 17:57:49 by mleproux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_free_all(char *stash, char *buffer)
{
	free(stash);
	return (free(buffer), NULL);
}

static char	*ft_build_line(char *stash, int fd)
{
	char	*buffer;
	char	*temp;
	int		byte;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	byte = 1;
	while (!ft_strchr(stash, '\n') && byte > 0)
	{
		byte = read(fd, buffer, BUFFER_SIZE);
		if (byte == -1)
			return (ft_free_all(stash, buffer));
		buffer[byte] = '\0';
		temp = ft_strjoin(stash, buffer);
		free(stash);
		stash = temp;
		if (!stash)
			return (ft_free_all(stash, buffer));
	}
	if (byte == 0 && stash[0] == '\0')
		return (ft_free_all(stash, buffer));
	return (free(buffer), stash);
}

static char	*ft_update_stash(char *stash)
{
	size_t	index;
	char	*new_stash;

	index = 0;
	while (stash[index] != '\n' && stash[index] != '\0')
		index++;
	if (stash[index] == '\0')
	{
		free(stash);
		return (NULL);
	}
	new_stash = ft_strndup(stash + index + 1, ft_strlen(stash) - index - 1);
	free(stash);
	return (new_stash);
}

char	*get_next_line_2(char *stash, int fd, char **line)
{
	size_t	index;

	stash = ft_build_line(stash, fd);
	if (!stash)
		return (NULL);
	index = 0;
	while (stash[index] != '\n' && stash[index] != '\0')
		index++;
	*line = ft_strndup(stash, index + 1);
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash[1024];
	char		*line;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	if (!stash[fd])
		stash[fd] = ft_strndup("", 1);
	stash[fd] = get_next_line_2(stash[fd], fd, &line);
	if (!stash[fd])
		return (NULL);
	stash[fd] = ft_update_stash(stash[fd]);
	if (ft_strlen(line) == 0)
	{
		free(line);
		line = NULL;
	}
	if (stash[fd] && ft_strlen(stash[fd]) == 0)
	{
		free(stash[fd]);
		stash[fd] = NULL;
	}
	return (line);
}
