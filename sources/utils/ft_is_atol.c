/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_atol.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:38:08 by tprovost          #+#    #+#             */
/*   Updated: 2025/03/18 10:34:44 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_is_atol_utils(char *str, int *i, int s, long *n)
{
	int		z;

	z = 0;
	while (str[*i + z] == '0')
	{
		z++;
		if (str[*i + z] == '\0')
			return (z);
	}
	while (str[(*i) + z] >= '0' && str[(*i) + z] <= '9')
	{
		(*n) = (10 * (*n)) + (str[(*i) + z] - 48) * s;
		(*i)++;
	}
	return (z);
}

int	ft_is_atol(char *str)
{
	int		i;
	int		z;
	int		s;
	long	n;

	i = 0;
	z = 0;
	s = 1;
	n = 0;
	if (str == NULL)
		return (0);
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			s = -1;
		i++;
	}
	if (str[i] == '\0')
		return (0);
	z = ft_is_atol_utils(str, &i, s, &n);
	if (str[i + z] != '\0' || (int)ft_strlen(str) > 20 + z
		|| n > 9223372036854775807 || n < -9223372036854775807 - 1
		|| ((int)ft_strlen(str) == 20 + z && str[0] != '+' && str[0] != '-'))
		return (0);
	return (1);
}
