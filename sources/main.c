/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:57:54 by tprovost          #+#    #+#             */
/*   Updated: 2025/02/13 16:07:43 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_data		data;
	char		*cmd_line;
	int			i;
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	cmd->input_fd = 0;
	cmd->output_fd = 0;
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
		i = 0;
		cmd->cmd_line = cmd_line;
		read_redirection(cmd);
		// ft_echo(cmd);
		// while (test[i])
		// {
		// 	printf("%s\n", test[i]);
		// 	i++;
		// }
		
		// parsing(data, str);
		// if (parsing(cmd_line) != 0)
		// {
		// 	// erreur
		// }
		// else
		// {
		// 	// execute(&data);
		// }
		free(cmd_line);
		cmd_line = readline(PROMPT);
		cmd_line = clean_cmd(cmd_line);
	}
	clear_history();
	free(cmd_line);
	// free(&data);
	return (0);
}
