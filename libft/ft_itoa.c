/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:37:31 by tprovost          #+#    #+#             */
/*   Updated: 2024/10/23 14:29:38 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

static int	nbcount(int nb)
{
	int	i;

	i = 0;
	while (nb > 0)
	{
		nb = nb / 10;
		i++;
	}
	return (i);
}

static int	power(int n, int p)
{
	int	nb;

	nb = 1;
	while (p > 0)
	{
		nb = nb * n;
		p = p - 1;
	}
	return (nb);
}

static char	*remp_itoa(int n, int s, int i, int ext)
{
	int		j;
	char	*str;

	str = (char *) malloc ((i + s + 1) * sizeof (char));
	if (str == NULL)
		return (NULL);
	j = i;
	str[i + s] = '\0';
	i = i - 1;
	while (i >= 0)
	{
		if (j - i < 10)
			str[i + s] = (n % power(10, j - i)) / power(10, j - i - 1) + 48;
		if (j - i == 10)
			str[i + s] = n / power(10, j - i - 1) + 48;
		i = i - 1;
	}
	str[ext] = str[ext] + ext;
	if (s == 1)
		str[0] = '-';
	return (str);
}

char	*ft_itoa(int n)
{
	int		i;
	int		s;
	int		ext;

	i = 0;
	s = 0;
	ext = 0;
	if (n == 0)
		i = 1;
	if (n < 0)
	{
		if (n == -2147483648)
		{
			n = -1147483648;
			ext = 1;
		}
		n = -n;
		s = 1;
	}
	i = i + nbcount(n);
	return (remp_itoa(n, s, i, ext));
}
/*
int	main(void)
{
	printf("%s\n", ft_itoa(-2147483647));
}*/
