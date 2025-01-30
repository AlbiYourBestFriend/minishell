/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:18:33 by tprovost          #+#    #+#             */
/*   Updated: 2024/10/24 13:33:52 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0' && (int)s[i] != (unsigned char)c)
		i++;
	if ((int)s[i] == (unsigned char)c)
		return ((char *)&(s[i]));
	return (NULL);
}
/*
int	main(void)
{
	printf("%s\n", ft_strchr("khrbg lr3 j4ty36j84 yd", '6'));
}*/
