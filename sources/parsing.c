/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:36:48 by mleproux          #+#    #+#             */
/*   Updated: 2025/02/03 19:27:33 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	command_len(char *input)
{
	int	index;

	index = 0;
	while (input[index] != '\0' && input[index] != PIPE)
		index++;
	return (index);
}

int	parsing(char *input)
{
	char		*cur_input;
	char		**splitted_input;
	t_command	*commands;
	int			index;

	index = 0;
	commands = NULL;
	while (input[index] != '\0')
	{
		cur_input = ft_strndup(input, command_len(input));
		splitted_input = ft_split(cur_input, ' ');
	}
	return (0);
}
