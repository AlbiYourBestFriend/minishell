/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:44:32 by mleproux          #+#    #+#             */
/*   Updated: 2025/02/20 18:12:40 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	heredoc_put_env_var_fd(t_data *data, char *buffer, int fd, int i)
{
	int			j;
	char		*name;
	t_env_var	*env_var;

	j = 0;
	while (buffer[i + j] != '\0' && ft_isspace(buffer[i + j]) == 0)
	{
		j++;
	}
	name = malloc((j + 1) * sizeof(char));
	j = 0;
	while (buffer[i + j] != '\0' && ft_isspace(buffer[i + j]) == 0)
	{
		name[j] = buffer[i + j];
		j++;
	}
	name[j] = '\0';
	env_var = get_env_var(data, name);
	if (env_var != NULL)
		ft_putstr_fd(env_var->value, fd);
	free(name);
	return (j);
}

static void	write_here_doc(t_data *data, char *buffer, int fd)
{
	int	i;

	i = 0;
	while (buffer[i] != '\0')
	{
		if (buffer[i] == '$')
		{
			i++;
			i = i + heredoc_put_env_var_fd(data, buffer, fd, i);
		}
		else
			ft_putchar_fd(buffer[i], fd);
		if (buffer[i] != '\0')
			i++;
	}
}

static int	get_here_doc(t_data *data, int fd, char *limiter)
{
	char	*buffer;

	buffer = NULL;
	while (1)
	{
		// signal_handler(1);
		buffer = readline("> ");
		if (buffer == NULL) // si buffer == NULL c'est qu'il y un ctrl+D
			return (0); // le heredoc doit etre fait quand meme
		else if ((ft_strncmp(buffer, limiter, INT_MAX) == 0))
			break ;
		write_here_doc(data, buffer, fd);
		write(fd, "\n", 1);
		free(buffer);
	}
	free(buffer);
	close(fd);
	return (1);
}

int	here_doc(t_data *data, int currentfd, char *limiter)
{
	int	fd;

	if (currentfd > 0)
		close(currentfd);
	fd = open(HEREDOCFILE, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (fd);
	if (get_here_doc(data, fd, limiter) == 0)
	{
		unlink(HEREDOCFILE);
		return (-1);
	}
	fd = open(HEREDOCFILE, O_RDONLY);
	if (fd < 0)
		unlink(HEREDOCFILE);
	return (fd);
}
