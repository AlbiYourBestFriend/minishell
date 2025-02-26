/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:44:32 by mleproux          #+#    #+#             */
/*   Updated: 2025/02/25 16:18:46 by tprovost         ###   ########.fr       */
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
		if (name != NULL)
			name[j] = buffer[i + j];
		j++;
	}
	if (name != NULL)
		name[j] = '\0';
	env_var = get_env_var(data, name);
	if (env_var != NULL)
		ft_putstr_fd(env_var->value, fd);
	if (name != NULL)
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
	ft_putchar_fd('\n', fd);
	free(buffer);
}

static void	get_here_doc(t_data *data, int fd, char *limiter)
{
	char	*buffer;
	int		tmp_count_line;

	tmp_count_line = 0;
	while (1)
	{
		buffer = readline("> ");
		if (buffer == NULL)
		{
			printf("warning: here-document at line %d ", data->count_line);
			printf("delimited by end-of-file (wanted `%s')\n", limiter);
			data->count_line += tmp_count_line;
			break ;
		}
		if ((ft_strncmp(buffer, limiter, INT_MAX) == 0))
		{
			tmp_count_line++;
			data->count_line += tmp_count_line;
			break ;
		}
		tmp_count_line++;
		write_here_doc(data, buffer, fd);
	}
	if (buffer != NULL)
		free(buffer);
}

int	here_doc(t_data *data, int currentfd, char *limiter)
{
	int	fd;

	if (currentfd > 0)
		close(currentfd);
	fd = open(HEREDOCFILE, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (fd);
	signal_handler(2);
	get_here_doc(data, fd, limiter);
	signal_handler(1);
	close(fd);
	fd = open(HEREDOCFILE, O_RDONLY);
	if (fd < 0)
		unlink(HEREDOCFILE);
	return (fd);
}
