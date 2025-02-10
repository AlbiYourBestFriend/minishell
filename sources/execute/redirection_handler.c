/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:08:49 by mleproux          #+#    #+#             */
/*   Updated: 2025/02/10 12:51:36 by mleproux         ###   ########.fr       */
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
int	open_infile_outfile(char **args)
{
	int	index;
	int	input;
	int	output;
	
	input = 0;
	output = 0;
	index = 0;
	while (args[index])
	{
		if (ft_strncmp(args[index], INPUT, INT_MAX) && args[index + 1])
			input = open_file(args[index + 1], input, 0, 0);
		else if (ft_strncmp(args[index], HEREDOC, INT_MAX) && args[index + 1])
			input = here_doc(input, args[index + 1]);
		else if (ft_strncmp(args[index], TRUNC, INT_MAX) && args[index + 1])
			output = open_file(args[index + 1], output, 1, 1);
		else if (ft_strncmp(args[index + 1], APPEND, INT_MAX) && args[index + 1])
			output = open_file(args[index + 1], output, 1, 0);
		if (input == -1 || output == -1)
			return (close_file(input, output), 0);
		index++;
	}
	return (1);
}
