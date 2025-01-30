/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:26:31 by mleproux          #+#    #+#             */
/*   Updated: 2024/10/28 12:51:23 by mleproux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	index;

	index = 0;
	while (index < n)
	{
		((char *)s)[index] = '\0';
		index++;
	}
}
/*
int	main()
{
	char	s[10] = "Bonjour";

	bzero(s, 5);
	printf("%s\n", s);
	printf("%s\n", &s[5]);
}
*/
