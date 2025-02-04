/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:57:54 by tprovost          #+#    #+#             */
/*   Updated: 2025/02/04 13:03:03 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	char	*cmd_line;
	char	*str;

	(void)argc;
	argv = NULL;
	data.env = ft_copy_tab(env);
	env = NULL;
	cmd_line = readline(PROMPT);
	str = ft_strtrim(cmd_line, " \t\v\n\f\r");
	// if (str[0] != '\0')
	// 	add_history(cmd_line);
	while (ft_strncmp(str, EXIT, ft_strlen(str)) != 0
		|| ft_strlen(str) != ft_strlen(EXIT))
	{
		ft_printf("%s\n", cmd_line);
		if (str[0] != '\0')
			add_history(cmd_line);
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
		str = ft_strtrim(cmd_line, " \t\v\n\f\r");
	}
	clear_history();
	free(str);
	free(cmd_line);
	ft_free_tab(data.env);
	return (0);
}
