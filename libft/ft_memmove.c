/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:15:28 by tprovost          #+#    #+#             */
/*   Updated: 2024/10/24 13:30:27 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*dest2;
	const char	*src2;

	src2 = src;
	dest2 = dest;
	if (dest == NULL && src == NULL)
		return (NULL);
	if (dest2 < src2)
	{
		i = -1;
		while (++i < n)
			dest2[i] = src2[i];
	}
	else
	{
		i = n + 1;
		while (--i > 0)
			dest2[i - 1] = src2[i - 1];
	}
	return (dest);
}
/*
int	main(void)
{
	char	str[20] = "Bonjour";
	printf("%s\n", str);
	printf("%s\n", &str[1]);
	printf("%s\n", (char *) ft_memmove(&str[1], str, 4));
	
}*/
