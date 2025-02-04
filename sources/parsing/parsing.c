/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:36:48 by mleproux          #+#    #+#             */
/*   Updated: 2025/02/04 13:28:23 by mleproux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// static int	command_len(char *input)
// {
// 	int	index;
	
// 	index = 0;
// 	while (input[index] != '\0' && input[index] != PIPE)
// 		index++;
// 	return (index);
// }

void	print_commands(t_data data)
{
	t_command	*temp;
	int			index;

	index = 0;
	temp = data.commands;
	while (temp)
	{
		printf("Command name: %s\n", temp->name);
		index = 0;
		printf("Args: ");
		if (!temp->args[index])
			printf("\tnone\n");
		while (temp->args[index])
		{
			printf("\t%s\n", temp->args[index]);
			index++;
		}
		temp = temp->next;
	}
}

int	parsing(t_data data, char *input)
{
	char	**splitted_cmds;
	char	**splitted_input;
	t_command	*cur_command;
	int	index;
	
	splitted_cmds = ft_split(input, PIPE);
	index = 0;
	while (splitted_cmds[index])
	{
		splitted_input = ft_split(splitted_cmds[index], ' ');
		cur_command = cmdnew(splitted_input);
		cmdadd_back(&data.commands, cur_command);
		index++;
	}
	print_commands(data);
	return (1);
}
