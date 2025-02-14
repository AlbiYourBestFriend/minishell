/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:57:54 by tprovost          #+#    #+#             */
/*   Updated: 2025/02/14 12:09:08 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	build_command(t_data *data, char *cmd_line)
{
	char	**cmds;
	int		index;

	index = 0;
	cmds = split_cmd_line(cmd_line, '|');
	while (cmds[index] != NULL)
	{
		cmdadd_back(&data->commands, cmdnew(cmds[index]));
		write(1, "1", 1);
		read_redirection(data->commands);
		write(1, "2", 1);
		ft_execute(data);
		write(1, "3", 1);
		index++;
		write(1, "f", 1);
		// if (builtin)
		// 	exec builtins
		// if else (env var)
		// 	handle env var
		// else
		// 	fork + execve
	}
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	char	*cmd_line;

	(void)argc;
	argv = NULL;
	data = init_data(env);
	cmd_line = readline(PROMPT);
	cmd_line = clean_cmd(cmd_line);
	while (ft_strncmp(cmd_line, EXIT, ft_strlen(cmd_line)) != 0
		|| ft_strlen(cmd_line) != ft_strlen(EXIT))
	{
		if (cmd_line[0] != '\0')
			add_history(cmd_line);
		build_command(&data, cmd_line);
		free(cmd_line);
		cmd_line = readline(PROMPT);
		cmd_line = clean_cmd(cmd_line);
	}
	clear_history();
	free(cmd_line);
	free_data(&data);
	return (0);
}
