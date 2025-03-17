/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 11:52:07 by tprovost          #+#    #+#             */
/*   Updated: 2025/03/17 11:57:29 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*open_here_doc_file(t_data *data, int *fd)
{
	char	*filename;
	char	*nbr_char;
	int		nbr;

	nbr = 1;
	while (1)
	{
		nbr_char = ft_itoa(nbr);
		if (nbr_char == NULL)
			return (allocate_error(ALLOC_ERR), NULL);
		filename = ft_strjoin(data->tmp_path, nbr_char);
		free(nbr_char);
		if (filename == NULL)
			return (allocate_error(ALLOC_ERR), NULL);
		if (access(filename, F_OK) == -1)
		{
			(*fd) = open(filename, O_CREAT | O_WRONLY, 0644);
			break ;
		}
		free(filename);
		nbr++;
	}
	if ((*fd) == -1)
		nofile_error(FILE_ERR, filename);
	return (filename);
}
