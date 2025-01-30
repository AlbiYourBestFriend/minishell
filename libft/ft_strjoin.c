/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:22:47 by tprovost          #+#    #+#             */
/*   Updated: 2024/10/22 15:09:01 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

char	*ft_strjoin(const char *s1, const char *s2)
{
	int		i;
	int		l1;
	int		l2;
	char	*str;

	i = 0;
	l1 = 0;
	l2 = 0;
	while (s1[l1] != '\0')
		l1++;
	while (s2[l2] != '\0')
		l2++;
	str = malloc ((l1 + l2 + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	while (i < l1 + l2)
	{
		if (i < l1)
			str[i] = s1[i];
		if (i >= l1)
			str[i] = s2[i - l1];
		i++;
	}
	str[i] = '\0';
	return (str);
}
/*
int	main(void)
{
	printf("%s\n", ft_strjoin("bon", "jour"));
}*/
