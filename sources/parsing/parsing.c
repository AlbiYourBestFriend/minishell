/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:36:48 by mleproux          #+#    #+#             */
/*   Updated: 2025/02/04 15:38:08 by tprovost         ###   ########.fr       */
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

static void	print_commands(t_data data)
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

static int	clean_cmds(char **cmds)
{
	char	*temp;
	int		index;

	index = 0;
	while (cmds[index])
	{
		temp = cmds[index];
		cmds[index] = ft_clean_cmd(cmds[index]);
		if (!cmds[index])
		{
			free_tab(cmds);
			free(temp);
			return (0);
		}
		free(temp);
		index++;
	}
	return (1);
}

int	parsing(t_data data, char *input)
{
	char	**splitted_cmds;
	// char	**splitted_input;
	// t_command	*cur_command;
	int	index;
	splitted_cmds = ft_split(input, PIPE);
	if (!clean_cmds(splitted_cmds))
		return (0);
	index = 0;
	while (splitted_cmds[index])
	{
		printf("cmd: %s\n", splitted_cmds[index]);
		// splitted_input = ft_split(splitted_cmds[index], ' ');
		// cur_command = cmdnew(splitted_input);
		// cmdadd_back(&data.commands, cur_command);
		index++;
	}
	print_commands(data);
	return (1);
}
