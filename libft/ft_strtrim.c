/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:34:47 by tprovost          #+#    #+#             */
/*   Updated: 2024/10/24 17:11:02 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

char	*ft_strtrim(const char *s1, const char *set)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (s1[len] != '\0')
		len++;
	while (ft_strrchr((char *)set, s1[len]))
		len--;
	while (ft_strchr(set, s1[i]))
		i++;
	return (ft_substr(s1, i, len - i + 1));
}
/*
int	main(void)
{
	printf("|%s|\n", ft_strtrim("- 	/ giugfreiug gr 	 *-", " /-*	"));
}*/