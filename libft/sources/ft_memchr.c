/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 09:39:36 by mleproux          #+#    #+#             */
/*   Updated: 2024/10/28 12:57:03 by mleproux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			index;
	unsigned char	*str;

	str = (unsigned char *)s;
	index = 0;
	while (n--)
	{
		if (str[index] == (unsigned char)c)
			return ((void *)&str[index]);
		index++;
	}
	return (NULL);
}
/*
int	main(void)
{
	char s[] = {0, 1, 2 ,3 ,4 ,5};
	printf("%s\n", (char*)ft_memchr(s,1, 6));	
}
*/
