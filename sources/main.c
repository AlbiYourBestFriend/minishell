/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:57:54 by tprovost          #+#    #+#             */
/*   Updated: 2025/02/17 18:45:45 by tprovost         ###   ########.fr       */
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
	char	*str;

	(void)argc;
	argv = NULL;
	data = init_data(env);
	// sig = 0;
	signal_handler(0);
	while (1)
	{
		cmd_line = readline(PROMPT);
		// printf("%s\n", cmd_line);
		if (cmd_line[0] != '\0')
		{
			add_history(cmd_line);
			str = clean_cmd(cmd_line);
			if (str[0] != '\0')
				build_command(&data, str);
			else
				free(str);
		}
		else
			free(cmd_line);
	}
	// rl_clear_history();
	// free(cmd_line);
	// free_data(&data);
	return (0);
}
