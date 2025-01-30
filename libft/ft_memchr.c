/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:33:39 by tprovost          #+#    #+#             */
/*   Updated: 2024/10/24 13:38:41 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*str;

	i = 0;
	str = s;
	if (n == 0)
		return (NULL);
	while (str[i] != (unsigned char)c && i < n - 1)
		i++;
	if (str[i] == (unsigned char)c)
		return ((void *)&(str[i]));
	return (NULL);
}
/*
int	main(void)
{
	printf("%s\n", (char *) ft_memchr("bonjour", 'n', 42));
}*/
