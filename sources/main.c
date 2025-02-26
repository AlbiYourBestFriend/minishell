/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:57:54 by tprovost          #+#    #+#             */
/*   Updated: 2025/02/25 15:56:23 by mleproux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

volatile int	g_exit_status;

static void	build_command(t_data *data, char *cmd_line)
{
	t_command	*temp;
	int			index;

	if (cmd_line[0] == '\0')
		return (free(cmd_line));
	index = 0;
	data->splitted_cmds = split_cmd_line(cmd_line, '|');
	free(cmd_line);
	if (data->splitted_cmds == NULL)
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
	ft_execute(data);
	free_cmds(data);
	free_tab(data->splitted_cmds);
	data->splitted_cmds = NULL;
}

static void	handle_ctrl_d(t_data *data)
{
	g_exit_status = 2;
	rl_clear_history();
	free_data(data);
	printf("exit\n");
	exit(g_exit_status);
}

static int	handle_cmd_line_extension(t_data *data, char *cmd_line)
{
	if (cmd_line == NULL)
	{
		printf("syntax error: unexpected end of file\n");
		handle_ctrl_d(data);
	}
	add_history(cmd_line);
	if (check_quotes(cmd_line) != 0)
	{
		printf("unexpected end of file near \
`%c'\n", (char)check_quotes(cmd_line));
		free(cmd_line);
		return (0);
	}
	return (1);
}

static void	handle_cmd_line(t_data *data, char *cmd_line)
{
	char	*token;
	char	*str;

	while (is_complete_cmd_line(cmd_line) == 0
		&& token_error(cmd_line) == 0)
		cmd_line = new_readline_join_cmd(data, cmd_line);
	if (handle_cmd_line_extension(data, cmd_line) == 0)
		return ;
	str = clean_cmd(cmd_line);
	if (str != NULL)
	{
		token = token_error(str);
		if (token == NULL && str[0] != '\0')
			build_command(data, str);
		else if (str[0] != '\0')
		{
			g_exit_status = 2;
			printf("syntax error near unexpected token `%s'\n", token);
			free(str);
		}
	}
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	char	*cmd_line;

	(void)argc;
	(void)argv;
	data = init_data(env);
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

// gerer g_exit_status et $?

/*

valgrind --leak-check=full --show-leak-kinds=all --suppressions=readline.supp ./minishell

*/
