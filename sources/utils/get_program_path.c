/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_program_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:50:54 by mleproux          #+#    #+#             */
/*   Updated: 2025/03/12 17:19:44 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	get_program_path(t_data *data, char *filelocation)
{
	char	path[MY_CHAR_MAX];

	getcwd(path, MY_CHAR_MAX);
	data->program_path = ft_strjoin(path, filelocation + 11);
	if (!data->program_path)
	{
		printf("%s Error: Couldn't allocate for program path.\n", ERREUR);
		free_data(data);
		exit(1);
	}
	data->tmp_path = ft_strjoin(data->program_path, "/.tmp/heredoc");
	if (!data->tmp_path)
	{
		printf("%s Error: Couldn't allocate for tmp path.\n", ERREUR);
		free_data(data);
		exit(1);
	}
}
