/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 18:17:22 by mleproux          #+#    #+#             */
/*   Updated: 2024/10/24 14:11:14 by mleproux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	index;
	char	*dest;
	size_t	s_len;

	s_len = ft_strlen(s);
	if (start > s_len)
		return (ft_strdup(""));
	else if (start + len >= s_len)
		len = s_len - start;
	dest = malloc(len + 1 * sizeof(char));
	if (dest == NULL)
		return (NULL);
	index = 0;
	while (index < len && s[index] != '\0')
	{
		dest[index] = s[start + index];
		index++;
	}
	dest[index] = '\0';
	return (dest);
}
/*
int	main(void)
{
	printf("%s\n", ft_substr("Bonjour", 1, 2));
	return (0);
}
*/
