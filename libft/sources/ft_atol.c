/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 14:52:36 by mleproux          #+#    #+#             */
/*   Updated: 2024/12/06 15:00:09 by mleproux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atol(const char *nptr)
{
	int		index;
	int		multiplier;
	long	result;

	multiplier = 1;
	result = 0;
	index = 0;
	while (nptr[index] == ' ' || nptr[index] == '\f' || nptr[index] == '\n'
		|| nptr[index] == '\r' || nptr[index] == '\t' || nptr[index] == '\v')
		index++;
	if (nptr[index] == '-' || nptr[index] == '+')
	{
		if (nptr[index] == '-')
			multiplier = -1;
		index++;
	}
	while (nptr[index] >= '0' && nptr[index] <= '9')
	{
		result = result * 10 + (nptr[index] - '0');
		index++;
	}
	return (result * multiplier);
}

// int	main(int argc, char **argv)
// {
// 	printf("%l", atol(argv[1]));
// 	printf("%l", ft_atol(argv[1]));
// }