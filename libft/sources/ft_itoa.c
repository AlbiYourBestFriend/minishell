/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 09:57:20 by mleproux          #+#    #+#             */
/*   Updated: 2024/11/18 11:52:37 by mleproux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_digitlen(int nb)
{
	int	count;

	count = 1;
	if (nb < 0)
	{
		count++;
		nb = nb * -1;
	}
	while (nb > 9)
	{
		nb = nb / 10;
		count++;
	}
	return (count);
}

static char	*ft_reversestr(char *str)
{
	int		index;
	int		index2;
	char	swap;

	index = 0;
	if (str[index] == '-')
		index++;
	index2 = ft_strlen(str) - 1;
	while (index < index2)
	{
		swap = str[index];
		str[index] = str[index2];
		str[index2] = swap;
		index++;
		index2--;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		index;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	else if (n == 0)
		return (ft_strdup("0"));
	str = ft_calloc(ft_digitlen(n) + 1, sizeof(char));
	if (str == NULL)
		return (NULL);
	index = 0;
	if (n < 0)
	{
		str[0] = '-';
		index++;
		n = n * -1;
	}
	while (n > 0)
	{
		str[index] = n % 10 + '0';
		n = n / 10;
		index++;
	}
	return (ft_reversestr(str));
}
/*
int	main(void)
{
	printf("%s\n",ft_itoa(1000));
}
*/
