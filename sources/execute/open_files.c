/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:08:49 by mleproux          #+#    #+#             */
/*   Updated: 2025/02/10 15:18:04 by mleproux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	open_file(char *filename, int currentfd, int isoutput, int dotrunc)
{
	int	fd;
	
	if (currentfd > 0)
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
static void	close_file(int input, int output)
{
	if (input > 0)
		close(input);
	if (output > 0)
		close(output);
}
static int	get_to_next_word(char *cmd, int	index)
{
	while (cmd[index] != '\0' && ft_isspace(cmd[index] == 1))
		index++;
	return (index);
}

int	open_files(char *cmd)
{
	int	index;
	int	input;
	int	output;
	int	redirection;
	
	input = 0;
	output = 0;
	index = 0;
	while (cmd[index])
	{
		redirection = get_redirection(cmd, index);
		if (redirection == INPUT)
		else if (redirection == HEREDOC)
		else if (redirection == TRUNC)
		else if (redirection == APPEND)
		index++;
	}
	return (1);
}
