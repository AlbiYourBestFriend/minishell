/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 10:11:17 by mleproux          #+#    #+#             */
/*   Updated: 2024/10/24 17:17:34 by mleproux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char		*ptr;
	size_t		index;

	if (size * nmemb > SIZE_MAX)
		return (NULL);
	ptr = malloc(nmemb * size);
	if (ptr == NULL)
		return (NULL);
	index = 0;
	while (index < nmemb * size)
	{
		ptr[index] = '\0';
		index++;
	}
	return ((void *)ptr);
}
/*
int	main(void)
{
	int	*array;
	int	index;

	array = malloc(5 * sizeof(int));
	index = 0;
	while (index++ < 5)
	{
		printf("%d : %d\n", index, array[index]);
	}
}
*/
