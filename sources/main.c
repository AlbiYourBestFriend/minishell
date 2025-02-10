/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:57:54 by tprovost          #+#    #+#             */
/*   Updated: 2025/02/10 18:15:32 by mleproux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	char	*cmd_line;
	char	*str;
	int	index;

	i = 0;

	(void)argc;
	argv = NULL;
	data = init_data(env);
	cmd_line = readline(PROMPT);
	cmd_line = clean_cmd(cmd_line);
	while (ft_strncmp(cmd_line, EXIT, ft_strlen(cmd_line)) != 0
		|| ft_strlen(cmd_line) != ft_strlen(EXIT))
	{
		ft_printf("%s\n", cmd_line);
		if (cmd_line[0] != '\0')
			add_history(cmd_line);
		index = 0;
		
		// while (test[index])
		// {
		// 	printf("%s\n", test[index]);
		// 	index++;
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
		free(str);
		free(cmd_line);
		free_tab(test);
		cmd_line = readline(PROMPT);
		cmd_line = clean_cmd(cmd_line);
	}
	clear_history();
	free(cmd_line);
	free_tab(data.env);
	return (0);
}
