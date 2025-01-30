/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:45:51 by mleproux          #+#    #+#             */
/*   Updated: 2024/10/24 13:19:44 by mleproux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		index;
	char		*dest2;
	const char	*src2;

	if (dest == NULL && src == NULL)
		return (NULL);
	dest2 = (char *)dest;
	src2 = (const char *)src;
	index = 0;
	while (index < n)
	{
		dest2[index] = src2[index];
		index++;
	}
	return (dest);
}

/*
int	main()
{
	char	dest[1] = ""; 
	printf("%s\n", (char*)memcpy(dest,"", 9));
	printf("%s\n", (char*)ft_memcpy(dest,"", 9));
}
*/