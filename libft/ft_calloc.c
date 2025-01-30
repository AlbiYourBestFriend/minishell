/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:30:03 by tprovost          #+#    #+#             */
/*   Updated: 2024/10/24 17:18:17 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	int		i;
	char	*s;

	i = 0;
	s = NULL;
	if (size != 0 && nmemb > 2147483648 / size)
		return (NULL);
	if (nmemb * size > 2147483647)
		return (NULL);
	s = (void *) malloc (nmemb * size);
	if (s == NULL)
		return (NULL);
	while (i < (int)(nmemb * size))
	{
		s[i] = 0;
		i++;
	}
	return ((void *)s);
}
