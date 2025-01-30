/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 08:56:36 by mleproux          #+#    #+#             */
/*   Updated: 2024/10/24 13:29:01 by mleproux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned const char	*p1;
	unsigned const char	*p2;
	size_t				index;

	p1 = (unsigned const char *)s1;
	p2 = (unsigned const char *)s2;
	index = 0;
	while ((p1[index] != '\0' || p2[index] != '\0') && index < n)
	{
		if (p1[index] != p2[index])
			return (p1[index] - p2[index]);
		index++;
	}
	return (0);
}
/*
int	main(void)
{
	printf("%d\n", strncmp("Bonjaur", "Bonjour", 8));
	printf("%d\n", ft_strncmp("Bonjaur", "Bonjour", 8));
	return (0);
}
*/
