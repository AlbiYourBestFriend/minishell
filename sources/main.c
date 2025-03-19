/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:57:54 by tprovost          #+#    #+#             */
/*   Updated: 2025/03/19 16:11:47 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

volatile int	g_exit_status;

static void	build_command(t_data *data, char *cmd_line)
{
	int			i;
	t_command	*temp;

	if (cmd_line[0] == '\0')
		return (free(cmd_line));
	i = -1;
	data->splitted_cmds = split_cmd_line(cmd_line, '|');
	free(cmd_line);
	if (data->splitted_cmds == NULL)
		return (allocate_error(ALLOC_ERR));
	while (data->splitted_cmds[++i] != NULL)
	{
		temp = cmdnew(data->splitted_cmds[i]);
		if (temp == NULL)
		{
			free_tab(data->splitted_cmds);
			data->splitted_cmds = NULL;
			return (free_cmds(data));
		}
		cmdadd_back(&data->commands, temp);
	}
	free_tab(data->splitted_cmds);
	data->splitted_cmds = NULL;
	return (ft_execute(data), free_cmds(data), unlink_tmp(data));
}

static void	handle_ctrl_d(t_data *data)
{
	printf("exit\n");
	free_all_exit(data, g_exit_status);
}

static int	handle_cmd_line_extension(t_data *data, char *cmd_line)
{
	if (cmd_line == NULL)
	{
		printf("%ssyntax error: %s\n", ERROR, UNEXPEC_EOF);
		handle_ctrl_d(data);
	}
	add_history(cmd_line);
	if (check_quotes(cmd_line) != 0)
	{
		printf("%s%s near `%c'\n", ERROR, UNEXPEC_EOF, \
								(char)check_quotes(cmd_line));
		free(cmd_line);
		return (0);
	}
	return (1);
}

static void	handle_cmd_line(t_data *data, char *cmd_line)
{
	char	*token;
	char	*str;

	while (is_complete_cmd_line(cmd_line) == 0 && token_error(cmd_line) == 0)
		cmd_line = new_readline_join_cmd(data, cmd_line);
	if (handle_cmd_line_extension(data, cmd_line) == 0)
		return ;
	str = clean_cmd(cmd_line);
	if (str == NULL)
	{
		allocate_error(ALLOC_ERR);
		data->exit_status = 1;
	}
	token = token_error(str);
	if (token == NULL && str[0] != '\0')
		build_command(data, str);
	else if (str[0] != '\0')
	{
		g_exit_status = 2;
		printf("%ssyntax error near unexpected token `%s'\n", \
				ERROR, token);
		free(str);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	char	*cmd_line;

	(void)argc;
	data = init_data(env, argv[0]);
	g_exit_status = 0;
	while (1)
	{
		signal_handler(0);
		cmd_line = readline(PROMPT);
		if (cmd_line == NULL)
			handle_ctrl_d(&data);
		data.count_line++;
		if (cmd_line[0] != '\0')
			handle_cmd_line(&data, cmd_line);
		else
			free(cmd_line);
	}
}

/*

clear && make && valgrind --leak-check=full 
--show-leak-kinds=all --trace-children=yes --track-fds=yes 
--suppressions=readline.supp ./minishell

*/
