/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:09:11 by mleproux          #+#    #+#             */
/*   Updated: 2024/11/20 10:52:50 by mleproux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putptr(unsigned int *arg)
{
	if (!arg)
		return (ft_putstr("(nil)"));
	write(1, "0x", 2);
	return (ft_putlhex((unsigned long)arg) + 2);
}
// int	main(void)
// {
// 	ft_putptr(0);
// 	printf("|%d|", printf("%p", (void *)0));
// }