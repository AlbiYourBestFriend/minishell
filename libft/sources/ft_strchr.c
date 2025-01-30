/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:33:51 by mleproux          #+#    #+#             */
/*   Updated: 2024/11/19 14:31:41 by mleproux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	c2;
	int		index;

	c2 = (char)c;
	index = 0;
	while (s[index] != '\0')
	{
		if (s[index] == c2)
			return ((char *)&s[index]);
		index++;
	}
	if (c2 == '\0')
		return ((char *)&s[index]);
	else
		return (NULL);
}
// int	main(void)
// {
// 	char	*str;

// 	str = ft_strchr("Bonjour", 'o');
// 	printf("%s\n", ft_strchr("Bonjour", 'o') + 1);
// }