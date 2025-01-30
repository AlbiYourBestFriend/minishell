/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 13:55:17 by mleproux          #+#    #+#             */
/*   Updated: 2024/10/25 16:34:46 by mleproux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
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
	index = 0;
	while (index < 5)
	{
		printf("%s\n", (char *)list->content);
		list = list->next;
		index++;
	}
}
*/