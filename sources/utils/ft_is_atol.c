/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_atol.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:38:08 by tprovost          #+#    #+#             */
/*   Updated: 2025/03/17 18:16:01 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_is_atol_utils(char *str, int *i, int *z, int n)
{
	int		s;

	s = 1;
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
		n = (10 * n) + (str[(*i) + (*z)] - 48) * s;
		(*i)++;
	}
	return (n);
}

int	ft_is_atol(char *str)
{
	int		i;
	int		z;
	long	n;

	i = 0;
	z = 0;
	n = 0;
	if (str == NULL)
		return (0);
	n = ft_is_atol_utils(str, &i, &z, n);
	if (str[i + z] != '\0' || (int)ft_strlen(str) > 19 + z
		|| n > 9223372036854775807 || n < -9223372036854775807 - 1)
		return (0);
	return (1);
}
