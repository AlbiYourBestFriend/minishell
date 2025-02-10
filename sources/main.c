/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:57:54 by tprovost          #+#    #+#             */
/*   Updated: 2025/02/10 18:36:34 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	char	*cmd_line;
	char 	**test;
	char	*str;
	int	i;

	i = 0;

	(void)argc;
	argv = NULL;
	data = init_data(env);
	cmd_line = readline(PROMPT);
	str = clean_cmd(cmd_line);
	while (ft_strncmp(str, EXIT, ft_strlen(str)) != 0
		|| ft_strlen(str) != ft_strlen(EXIT))
	{
		ft_printf("%s\n", str);
		if (str[0] != '\0')
			add_history(cmd_line);
		test = split_cmd_line(str, '|');
		i = 0;
		while (test[i] != NULL)
		{
			printf("test[%d] = %s\n", i, test[i]);
			i++;
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
		free_tab(test);
		cmd_line = readline(PROMPT);
		str = clean_cmd(cmd_line);
	}
	clear_history();
	free(str);
	free(cmd_line);
	free_tab(data.my_env);
	return (0);
}
