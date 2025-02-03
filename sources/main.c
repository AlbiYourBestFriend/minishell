/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:57:54 by tprovost          #+#    #+#             */
/*   Updated: 2025/02/03 19:26:59 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	char	*cmd_line;

	(void)argc;
	argv = NULL;
	data.env = ft_copy_tab(env);
	env = NULL;
	cmd_line = readline(PROMPT);
	add_history(cmd_line);
	while (ft_strncmp(ft_strtrim(cmd_line, " \t\v\n\f\r"), EXIT, ft_strlen(ft_strtrim(cmd_line, " \t\v\n\f\r"))) != 0
		|| ft_strlen(ft_strtrim(cmd_line, " \t\v\n\f\r")) != ft_strlen(EXIT))
	{
		ft_printf("%s\n", cmd_line);
		if (cmd_line[0] != '\0')
			add_history(cmd_line);
		// if (parsing(cmd_line) != 0)
		// {
		// 	// erreur
		// 	clear_history();
		// 	free(cmd_line);
		// 	ft_free_tab(data.env);
		// 	return (0);
		// }
		// else
		// {
		// 	// execute
		// }
		free(cmd_line);
		cmd_line = readline(PROMPT);
	}
	clear_history();
	free(cmd_line);
	ft_free_tab(data.env);
	return (0);
}
