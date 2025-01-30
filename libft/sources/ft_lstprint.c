/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 16:30:53 by mleproux          #+#    #+#             */
/*   Updated: 2024/11/25 10:08:24 by mleproux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstprint(t_list *lst, char *specifier)
{
	int	index;

	index = 0;
	while (lst)
	{
		if (ft_strchr(specifier, 'd'))
			ft_printf(specifier, *(int *)lst->content);
		else
			ft_printf(specifier, lst->content);
		lst = lst->next;
		index++;
	}
	return (index);
}
/*
int	main(void)
{
	t_list	*list;
	t_list	*newlist;
	int		index;
	
	list = ft_lstnew("0");
	index = 1;
	while (index < 5)
	{
		newlist = ft_lstnew(ft_itoa(index));
		ft_lstadd_front(&list, newlist);
		index++;
	}
	printf("%d", ft_lstsize(list));
}
*/