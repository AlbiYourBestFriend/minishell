/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:51:04 by mleproux          #+#    #+#             */
/*   Updated: 2025/04/02 16:59:55 by mleproux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_isdir(char *path)
{
	struct stat buf;

    if (stat(path, &buf) != 0) 
        return (allocate_error(ALLOC_ERR), 0);
    if (S_ISDIR(buf.st_mode))
        return (noperm_error("Is a directory", path), 1);
    else
        return (0);
}