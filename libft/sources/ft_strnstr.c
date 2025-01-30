/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:31:59 by mleproux          #+#    #+#             */
/*   Updated: 2024/10/25 11:50:11 by mleproux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	index;
	size_t	index2;

	if (little[0] == '\0')
		return ((char *)big);
	index = 0;
	index2 = 0;
	while (big[index] != '\0' && index < len)
	{
		index2 = 0;
		while (index + index2 < len && little[index2] == big[index + index2]
			&& little[index2])
			index2++;
		if (little[index2] == '\0')
			return ((char *)&big[index]);
		index++;
	}
	return (NULL);
}
/*
int	main(void)
{
	printf("%s\n", ft_strnstr("Bonjour les amis", "Bonjour les amis", 15));
	return (0);
}
*/
