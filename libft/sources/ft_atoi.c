/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 09:18:24 by mleproux          #+#    #+#             */
/*   Updated: 2024/12/06 14:54:45 by mleproux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	index;
	int	multiplier;
	int	result;

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
/*
int	main(int argc, char **argv)
{
	if (argc == 1)
	{
		printf("Missing argument #1");
		return (0);
	}
	printf("True fonction : %d\n", atoi(argv[1]));
	printf("My fonction : %d\n", ft_atoi(argv[1]));
}
*/
