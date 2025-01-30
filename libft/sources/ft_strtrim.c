/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 14:07:45 by mleproux          #+#    #+#             */
/*   Updated: 2024/10/25 11:49:09 by mleproux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		index;
	int		slen;

	slen = ft_strlen(s1);
	index = 0;
	while (ft_strchr(set, s1[index]))
		index++;
	while (ft_strchr(set, s1[slen]))
		slen--;
	return (ft_substr(s1, index, slen - index + 1));
}
/*
int	main(int argc, char **argv)
{
	char	c;
	
	c = 'o';
	argc += 5;
	printf("%s\n", ft_strtrim(argv[1], &c));
}
*/