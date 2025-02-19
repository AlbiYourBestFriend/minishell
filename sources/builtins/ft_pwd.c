/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:31:22 by mleproux          #+#    #+#             */
/*   Updated: 2025/02/19 17:12:36 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_pwd(t_data *data)
{
	char	path[MY_CHAR_MAX];

	(void)data;
	if (getcwd(path, MY_CHAR_MAX))
	{
		ft_putstr_fd(path, 1);
		write(1, "\n", 1);
		return ;
	}
	else
	{
		perror("erreur");
		return ;
	}
}
