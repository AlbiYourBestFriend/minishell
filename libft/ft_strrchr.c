/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:24:34 by tprovost          #+#    #+#             */
/*   Updated: 2024/10/25 13:27:34 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

char	*ft_strrchr(char *s, int c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if ((int)s[i] == (unsigned char)c)
			j = i;
		i++;
	}
	if ((unsigned char)c == '\0')
		j = i;
	if ((int)s[j] == (unsigned char)c)
		return ((char *)&(s[j]));
	return (NULL);
}
/*
int	main(void)
{
	printf("%s\n", ft_strrchr("khrb6g lr3 j4ty36j846 yd", '\0'));
}*/
