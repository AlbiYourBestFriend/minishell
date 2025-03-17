/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_atoi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:38:08 by tprovost          #+#    #+#             */
/*   Updated: 2025/03/17 17:57:35 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_is_atoi_utils(char *str, int *i, int (*z), int n)
{
	int		s;

	if (str[*i] == '+' || str[*i] == '-')
	{
		if (str[*i] == '-')
			s = -1;
		(*i)++;
	}
	while (str[*i + (*z)] == '0')
	{
		(*z)++;
		if (str[*i + (*z)] == '\0')
			return (0);
	}
	while (str[(*i) + (*z)] >= '0' && str[(*i) + (*z)] <= '9')
	{
		n = (10 * n) + str[(*i) + (*z)] - 48;
		(*i)++;
	}
	n = n * s;
	return (n);
}

int	ft_is_atoi(char *str)
{
	int		i;
	int		z;
	long	n;

	i = 0;
	z = 0;
	n = 0;
	if (str == NULL)
		return (0);
	n = ft_is_atoi_utils(str, &i, &z, n);
	if (str[i + z] != '\0' || (int)ft_strlen(str) > 11 + z
		|| n > 2147483647 || n < -2147483648)
		return (0);
	return (1);
}
