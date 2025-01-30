/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 13:25:06 by tprovost          #+#    #+#             */
/*   Updated: 2024/10/25 13:27:23 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

static void	sub_remp(const char *s, char *dest, unsigned int start, size_t len)
{
	unsigned int	i;

	i = 0;
	while (i < len && s[start + i] != '\0')
	{
		dest[i] = s[start + i];
		i++;
	}
	dest[i] = '\0';
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*dest;

	i = 0;
	while (s[i] != '\0')
		i++;
	if (start >= i)
	{
		dest = malloc(sizeof(char));
		if (dest == NULL)
			return (NULL);
		dest[0] = '\0';
	}
	else
	{
		i = 0;
		while (s[start + i] != '\0' && i < len)
			i++;
		dest = malloc ((i + 1) * sizeof(char));
		if (dest == NULL)
			return (NULL);
		sub_remp(s, dest, start, len);
	}
	return (dest);
}
/*
int	main(void)
{
	printf("%s\n", ft_substr("bonjour", 8, 5));
}*/
