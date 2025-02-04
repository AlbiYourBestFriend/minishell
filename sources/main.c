/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:57:54 by tprovost          #+#    #+#             */
/*   Updated: 2025/02/03 17:12:22 by mleproux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **env)
{
	// t_data	data;
	char	*cmd_line;
	(void)argc;
	argv = NULL;
	env = NULL;
	cmd_line = readline(PROMPT);
	while (ft_strncmp(ft_strtrim(cmd_line, " \t\v\n\f\r"), EXIT, ft_strlen(ft_strtrim(cmd_line, " \t\v\n\f\r"))) != 0)
	{
		parsing(cmd_line);
		free(cmd_line);
		cmd_line = readline(PROMPT);
	}
	free(cmd_line);
	return (0);
}
