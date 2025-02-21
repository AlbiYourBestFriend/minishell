/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_atoi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:38:08 by tprovost          #+#    #+#             */
/*   Updated: 2025/02/21 14:57:55 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_is_atoi(char *str)
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
		if (str[i++] == '-')
			s = -1;
	}
	while (str[i + z] == '0')
		z++;
	i -= 1;
	while (str[++i + z] >= '0' && str[i + z] <= '9')
		n = (10 * n) + str[i + z] - 48;
	if (str[i] != '\0' || (int)ft_strlen(str) > 11 + z
		|| n > 2147483647 || n < -2147483648)
		return (0);
	return (1);
}
