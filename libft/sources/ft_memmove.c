/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 09:32:19 by mleproux          #+#    #+#             */
/*   Updated: 2024/10/25 11:49:27 by mleproux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*dest2;
	const char	*src2;
	size_t		index;

	if (dest == NULL && src == NULL)
		return (NULL);
	dest2 = dest;
	src2 = src;
	index = 0;
	if (dest2 < src2)
	{
		while (index < n)
		{
			dest2[index] = src2[index];
			index++;
		}
	}
	else
	{
		index = n + 1;
		while (--index > 0)
			dest2[index - 1] = src2[index - 1];
	}
	return (dest);
}

/*
int	main(void)
{
	char	src[50] = "Bonjour"; 
	printf("%s\n",(char*)ft_memmove(&src[1], src, 4));
}
*/
