/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:31:22 by mleproux          #+#    #+#             */
/*   Updated: 2025/04/02 18:01:25 by mleproux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_pwd(void)
{
	char	path[MY_CHAR_MAX];

	if (getcwd(path, MY_CHAR_MAX) != NULL)
	{
		ft_putstr_fd(path, 1);
		ft_putstr_fd("\n", 1);
		g_exit_status = 0;
	}
	else
	{
		ft_putstr_fd("Minishell: Error executing pwd\n", 1);
		g_exit_status = 1;
	}
}
