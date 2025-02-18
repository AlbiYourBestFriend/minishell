/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:57:54 by tprovost          #+#    #+#             */
/*   Updated: 2025/02/18 18:49:27 by tprovost         ###   ########.fr       */
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
	free(cmd_line);
	if (!cmds)
	{
		printf("Erreur");
		return ;
	}
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
	// free_cmds(data);
	// free_tab(cmds);
}

volatile int	g_exit_status;

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	char	*cmd_line;
	char	*str;

	(void)argc;
	argv = NULL;
	g_exit_status = 0;
	data = init_data(env);
	while (1)
	{
		signal_handler(0);
		cmd_line = readline(PROMPT);
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
	rl_clear_history();
	free_data(&data);
	return (g_exit_status);
}
