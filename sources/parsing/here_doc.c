/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:44:32 by mleproux          #+#    #+#             */
/*   Updated: 2025/03/13 17:39:00 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	heredoc_put_env_var_fd(t_data *data, char *buffer, int fd, int *i)
{
	int			j;
	char		*name;
	t_env_var	*env_var;

	j = 0;
	while (buffer[(*i) + j] != '\0' && ft_isspace(buffer[(*i) + j]) == 0)
		j++;
	name = malloc((j + 1) * sizeof(char));
	if (name == NULL)
		return (allocate_error(ALLOC_ERR), 0);
	j = 0;
	while (buffer[(*i) + j] != '\0' && ft_isspace(buffer[(*i) + j]) == 0)
	{
		name[j] = buffer[(*i) + j];
		j++;
	}
	name[j] = '\0';
	env_var = get_env_var(data, name);
	if (env_var != NULL)
		ft_putstr_fd(env_var->value, fd);
	free(name);
	(*i) += j;
	return (1);
}

static int	write_here_doc(t_data *data, char *buffer, int fd)
{
	int	i;

	i = 0;
	while (buffer[i] != '\0')
	{
		if (buffer[i] == '$')
		{
			i++;
			if (heredoc_put_env_var_fd(data, buffer, fd, &i) == 0)
				return (0);
		}
		else
			ft_putchar_fd(buffer[i], fd);
		if (buffer[i] != '\0')
			i++;
	}
	ft_putchar_fd('\n', fd);
	free(buffer);
	return (1);
}

static int	get_here_doc(t_data *data, int fd, char *limiter)
{
	char	*buffer;
	int		tmp_count_line;

	tmp_count_line = 0;
	while (1)
	{
		buffer = readline("> ");
		if (buffer == NULL)
		{
			printf("%swarning: here-document at line %d ", \
					ERROR, data->count_line);
			printf("delimited by end-of-file (wanted `%s')\n", limiter);
			data->count_line += tmp_count_line;
			return (1);
		}
		if (ft_strncmp(buffer, limiter, INT_MAX) == 0)
		{
			tmp_count_line++;
			data->count_line += tmp_count_line;
			return (free(buffer), 1);
		}
		tmp_count_line++;
		if (write_here_doc(data, buffer, fd) == 0)
			return (free(buffer), 0);
	}
}

char	*open_here_doc_file(t_data *data, int *fd)
{
	char	*filename;
	char	*nbr_char;
	int		nbr;

	nbr = 1;
	while (1)
	{
		nbr_char = ft_itoa(nbr);
		if (nbr_char == NULL)
			return (allocate_error(ALLOC_ERR), NULL);
		filename = ft_strjoin(data->tmp_path, nbr_char);
		free(nbr_char);
		if (filename == NULL)
			return (allocate_error(ALLOC_ERR), NULL);
		if (access(filename, F_OK) == -1)
		{
			(*fd) = open(filename, O_CREAT | O_WRONLY, 0644);
			break ;
		}
		free(filename);
		nbr++;
	}
	if ((*fd) == -1)
		nofile_error(FILE_ERR, filename);
	return (filename);
}

int	here_doc(t_data *data, int currentfd, char *limiter)
{
	int		fd;
	char	*filename;

	if (currentfd > 0)
		close(currentfd);
	fd = 0;
	filename = open_here_doc_file(data, &fd);
	if (fd < 0)
		return (free(filename), fd);
	signal_handler(2);
	if (get_here_doc(data, fd, limiter) == 0)
		return (free(filename), close(fd), -1);
	signal_handler(1);
	close(fd);
	if (access(filename, O_RDONLY) == -1)
	{
		nofile_error(NO_PERM, filename);
		return (free(filename), -1);
	}
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		nofile_error(NO_FILE_DIR, filename);
	free(filename);
	return (fd);
}
