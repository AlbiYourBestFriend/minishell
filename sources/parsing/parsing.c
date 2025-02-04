/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:36:48 by mleproux          #+#    #+#             */
/*   Updated: 2025/02/04 11:46:29 by mleproux         ###   ########.fr       */
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

int	parsing(char *input)
{
	char	**splitted_cmds;
	char	**splitted_input;
	t_command	*commands;
	t_command	*cur_command;
	int	index;
	
	splitted_cmds = ft_split(input, PIPE);
	commands = NULL;
	index = 0;
	while (splitted_cmds[index])
	{
		splitted_input = ft_split(splitted_cmds[index], ' ');
		cur_command = cmdnew(splitted_input);
		cmdadd_back(&commands, cur_command);
		index++;
	}
	while (commands)
	{
		printf("Command name: %s\n", commands->name);
		index = 0;
		printf("Args: ");
		if (!commands->args[index])
			printf("\tnone\n");
		while (commands->args[index])
		{
			printf("\t%s\n", commands->args[index]);
			index++;
		}
		commands = commands->next;
	}
	return (1);
}
