/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 16:48:57 by tprovost          #+#    #+#             */
/*   Updated: 2024/10/15 16:51:26 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putnbr_fd(int nb, int fd)
{
	char	c;

	if (nb < 0)
	{
		write(fd, "-", 1);
		if (nb == -2147483648)
		{
			write(fd, "2", 1);
			nb = -147483648;
		}
		nb = nb * (-1);
	}
	if (nb > 9)
	{
		ft_putnbr_fd(nb / 10, fd);
	}
	c = nb % 10 + '0';
	write(fd, &c, 1);
}
/*
int	main(void)
{
	int	n;

	n = -2147483648;
	ft_putnbr_fd(n, 1);
}*/
