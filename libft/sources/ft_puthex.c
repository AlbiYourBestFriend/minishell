/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 13:09:26 by mleproux          #+#    #+#             */
/*   Updated: 2024/11/20 10:53:09 by mleproux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putuhex(unsigned long nbr)
{
	int		len;
	int		remainder;
	char	hex;

	len = 1;
	if (nbr >= 16)
		len = len + ft_putuhex(nbr / 16);
	remainder = nbr % 16;
	if (remainder < 10)
		hex = remainder + '0';
	else
		hex = remainder - 10 + 'A';
	write(1, &hex, 1);
	return (len);
}

int	ft_putlhex(unsigned long nbr)
{
	int				len;
	int				remainder;
	char			hex;

	len = 1;
	if (nbr >= 16)
		len = len + ft_putlhex(nbr / 16);
	remainder = nbr % 16;
	if (remainder < 10)
		hex = remainder + '0';
	else
		hex = remainder - 10 + 'a';
	write(1, &hex, 1);
	return (len);
}
