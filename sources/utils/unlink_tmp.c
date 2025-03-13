/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unlink_tmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:15:40 by mleproux          #+#    #+#             */
/*   Updated: 2025/03/13 11:46:24 by mleproux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	unlink_tmp(t_data *data)
{
	int		nbr;
	char	*nbr_char;
	char	*temp;

	nbr = 1;
	while (1)
	{
		nbr_char = ft_itoa(nbr);
		if (nbr_char == NULL)
			return (allocate_error(ALLOC_ERR));
		temp = ft_strjoin(data->tmp_path, nbr_char);
		free(nbr_char);
		if (temp == NULL)
			return (allocate_error(ALLOC_ERR));
		if (access(temp, F_OK) == -1)
			break ;
		else if (access(temp, W_OK) == 0)
			unlink(temp);
		free(temp);
		nbr++;
	}
	free(temp);
}
