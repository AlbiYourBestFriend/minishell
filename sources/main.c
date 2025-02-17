/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:57:54 by tprovost          #+#    #+#             */
/*   Updated: 2025/02/17 12:39:58 by mleproux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	build_command(t_data *data, char *cmd_line)
{
	char		**cmds;
	t_command	*temp;
	int			index;

	index = 0;
	cmds = split_cmd_line(cmd_line, '|');
	while (cmds[index] != NULL)
	{
		cmdadd_back(&data->commands, cmdnew(cmds[index]));
		index++;
	}
	temp = data->commands;
	while (temp)
	{
		read_redirection(temp);
		temp = temp->next;
	}
	ft_execute(data);
	free_cmds(data);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	char	*cmd_line;

	(void)argc;
	argv = NULL;
	data = init_data(env);
	while (1)
	{
		cmd_line = readline(PROMPT);
		cmd_line = clean_cmd(cmd_line);
		if (cmd_line[0] != '\0')
			add_history(cmd_line);
		build_command(&data, cmd_line);
		free(cmd_line);
	}
	clear_history();
	free(cmd_line);
	free_data(&data);
	return (0);
}
