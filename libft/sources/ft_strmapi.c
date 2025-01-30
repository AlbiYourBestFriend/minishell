/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 12:53:57 by mleproux          #+#    #+#             */
/*   Updated: 2024/10/24 16:33:59 by mleproux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	index;
	char			*s2;

	s2 = malloc(ft_strlen(s) + 1);
	if (!s2)
		return (NULL);
	index = 0;
	while (s[index] != '\0')
	{
		s2[index] = f(index, s[index]);
		index++;
	}
	s2[index] = '\0';
	return (s2);
}
/*
static char to_upandlow(unsigned int index, char chr)
{

    if ((chr >= 'a' && chr <= 'z') && index % 2 == 0)
        chr -= 32;
    else if ((chr >= 'A' && chr <= 'Z') && index % 2 != 0)
        chr += 32;

    return chr;
}

int	main(void)
{
	printf("%s\n", ft_strmapi("HELLO WORLD!", to_upandlow));
}
*/
