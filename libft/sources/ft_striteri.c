/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:16:16 by mleproux          #+#    #+#             */
/*   Updated: 2024/10/28 11:32:01 by mleproux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	index;

	index = 0;
	while (s[index] != '\0')
	{
		f(index, &s[index]);
		index++;
	}
}
/*
static void to_upandlow(unsigned int index, char *chr)
{

    if ((chr[index] >= 'a' && chr[index] <= 'z') && index % 2)
        chr[index] -= 32;
    else if ((chr[index] >= 'A' && chr[index] <= 'Z') && index % 2 == 0)
        chr[index] += 32;

    return (void)chr;
}

int	main(void)
{
	char	str[13] = "hello world!";

	printf("before : %s\n", str);
	ft_striteri(str, to_upandlow);
	printf("after : %s\n", str);
}
*/
