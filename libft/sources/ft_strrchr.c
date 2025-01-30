/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 08:44:54 by mleproux          #+#    #+#             */
/*   Updated: 2024/10/23 14:46:07 by mleproux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		index;
	char	c2;

	c2 = (char)c;
	index = ft_strlen(s);
	if (c2 == '\0')
		return ((char *)&s[index]);
	while (index > -1)
	{
		if (s[index] == c2)
			return ((char *)&s[index]);
		index--;
	}
	return (NULL);
}
/*
int	main(void)
{
	printf("%s\n", ft_strrchr("Bonjour", 'o' + 256));
	return (0);
}
*/
