/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 16:27:47 by tprovost          #+#    #+#             */
/*   Updated: 2024/10/15 16:31:55 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	if (s != NULL && f != NULL)
	{
		while (s[i] != '\0')
		{
			f(i, &s[i]);
			i++;
		}
	}
}
/*
void	ft_plus(unsigned int i, char *s)
{
	char	c;

	c = s[i] + i;
	s[i] = c;
}

int	main(void)
{
	char	str[30] = "salut 0123456789";

	ft_striteri(str, &ft_plus);
	printf("%s\n", str);
}*/
