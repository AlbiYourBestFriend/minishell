/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:46:12 by mleproux          #+#    #+#             */
/*   Updated: 2024/11/19 14:31:37 by mleproux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	int		index;
	int		index2;

	dest = malloc(sizeof(char) * ft_strlen(s1) + ft_strlen(s2) + 1);
	if (dest == NULL)
		return (NULL);
	index = 0;
	while (s1[index] != '\0')
	{
		dest[index] = s1[index];
		index++;
	}
	index2 = 0;
	while (s2[index2] != '\0')
	{
		dest[index + index2] = s2[index2];
		index2++;
	}
	dest[index + index2] = '\0';
	return (dest);
}
// int	main(int argc, char **argv)
// {
// 	(void)argc;
// 	printf("%s\n", ft_strjoin(NULL, argv[2]));
// }