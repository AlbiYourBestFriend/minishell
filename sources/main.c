/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:57:54 by tprovost          #+#    #+#             */
/*   Updated: 2025/02/06 13:27:08 by mleproux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	char	*cmd_line;
	char **test;
	char	*str;
	int	index;

	index = 0;

	(void)argc;
	argv = NULL;
	data = init_data(env);
	cmd_line = readline(PROMPT);
	str = ft_clean_cmd(cmd_line);
	while (ft_strncmp(str, EXIT, ft_strlen(str)) != 0
		|| ft_strlen(str) != ft_strlen(EXIT))
	{
		ft_printf("%s\n", str);
		if (str[0] != '\0')
			add_history(cmd_line);
		test = pipe_split(str, '|');
		index = 0;
		while (test[index])
		{
			printf("%s\n", test[index]);
			index++;
		}
		
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
		cmd_line = readline(PROMPT);
		str = ft_clean_cmd(cmd_line);
	}
	clear_history();
	free(str);
	free(cmd_line);
	free_tab(data.env);
	return (0);
}
