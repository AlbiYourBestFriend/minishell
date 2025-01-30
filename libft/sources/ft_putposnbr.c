/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putposnbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 11:25:51 by mleproux          #+#    #+#             */
/*   Updated: 2024/11/20 10:52:53 by mleproux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putposnbr(unsigned int nbr)
{
	char	*str;
	int		len;

	str = ft_uitoa(nbr);
	len = ft_strlen(str);
	write(1, str, len);
	free(str);
	return (len);
}
