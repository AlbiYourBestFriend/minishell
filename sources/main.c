/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:57:54 by tprovost          #+#    #+#             */
/*   Updated: 2025/02/18 12:10:31 by mleproux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	build_command(t_data *data, char *cmd_line)
{
	t_command	*temp;
	int			index;

	index = 0;
	data->splitted_cmds = split_cmd_line(cmd_line, '|');
	free(cmd_line);
	if (!data->splitted_cmds)
	{
		printf("Erreur");
		return ;
	}
	while (data->splitted_cmds[index] != NULL)
	{
		cmdadd_back(&data->commands, cmdnew(data->splitted_cmds[index]));
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
	free_tab(data->splitted_cmds);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	char	*cmd_line;
	char	*str;

	(void)argc;
	argv = NULL;
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
	clear_history();
	free_data(&data);
	return (0);
}
