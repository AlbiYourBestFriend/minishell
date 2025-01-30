/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:12:37 by mleproux          #+#    #+#             */
/*   Updated: 2024/11/20 10:51:28 by mleproux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_var_type(char specifier, va_list args)
{
	int	count;

	if (specifier == 'c')
		count = ft_putchar(va_arg(args, int));
	if (specifier == 's')
		count = ft_putstr(va_arg(args, char *));
	if (specifier == 'p')
		count = ft_putptr(va_arg(args, void *));
	if (specifier == 'd' || specifier == 'i')
		count = ft_putnbr(va_arg(args, int));
	if (specifier == 'u')
		count = ft_putposnbr(va_arg(args, unsigned int));
	if (specifier == 'x')
		count = ft_putlhex(va_arg(args, unsigned int));
	if (specifier == 'X')
		count = ft_putuhex(va_arg(args, unsigned int));
	if (specifier == '%')
	{
		return (write(1, "%", 1));
		count = 1;
	}
	return (count);
}

int	ft_printf(const char *parsing, ...)
{
	int		index;
	int		count;
	va_list	args;

	va_start(args, parsing);
	index = 0;
	count = 0;
	while (parsing[index] != '\0')
	{
		if (parsing[index] == '%')
		{
			count += check_var_type(parsing[index + 1], args);
			index += 2;
		}
		else
		{
			write(1, &parsing[index], 1);
			count++;
			index++;
		}
	}
	va_end(args);
	return (count);
}

// int	main()
// {
// 	int	my_printf;
// 	int true_printf;
// 	my_printf = ft_printf("string : %p %s\n", NULL, NULL);
// 	true_printf = printf("string : %p %s\n", NULL, NULL);
// 	printf("My printf: %d\nTrue printf: %d\n", my_printf, true_printf);
// }