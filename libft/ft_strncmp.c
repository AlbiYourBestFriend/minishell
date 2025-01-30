/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:31:19 by tprovost          #+#    #+#             */
/*   Updated: 2024/10/24 10:47:36 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n)
	{
		if (s1[i] != s2[i] || s1[i] == '\0' || s2[i] == '\0')
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}
/*
#include <string.h>

int	main(void)
{
	const char	*a;
	const char	*b;
	int			i;
	
	a = "test\200";
	b = "test\0";
	i = 6;
	printf("strncmp    : %d\n", strncmp(a, b, i));
	printf("ft_strncmp : %d\n", ft_strncmp(a, b, i));
	printf("%d %d\n", a[4], b[4]);
}*/
