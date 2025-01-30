/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 09:58:37 by tprovost          #+#    #+#             */
/*   Updated: 2024/10/24 09:55:22 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	j = 0;
	while (dest[j] != '\0' && j < size)
		j++;
	i = 0;
	while (src[i] != '\0')
		i++;
	if (size == j)
		return (size + i);
	i = 0;
	while (src[i] != '\0' && i < size - j - 1)
	{
		dest[j + i] = src[i];
		i++;
	}
	dest[j + i] = '\0';
	while (src[i] != '\0')
		i++;
	return (j + i);
}
/*
#include <string.h>

#include <stddef.h>

int	main(void)
{
	char	a[10] = "aff";
	char	*b = "lorem ipsum dolor sit amet";
	size_t	i;

	i = 1;
	printf("%d\n", (int)ft_strlcat(a, b, i));
	printf("%d\n", (int)strlcat(a, b, i));
	printf("%s\n", a);
}*/
