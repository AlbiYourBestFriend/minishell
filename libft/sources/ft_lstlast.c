/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 16:47:14 by mleproux          #+#    #+#             */
/*   Updated: 2024/10/28 11:40:52 by mleproux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*temp;

	if (!lst)
		return (NULL);
	temp = lst;
	while (temp->next != NULL)
		temp = temp->next;
	return (temp);
}

/*
int	main(void)
{
	t_list	*list;
	t_list	*newlist;
	int		index;
	
	list = ft_lstnew("1");
	index = 2;
	while (index < 7)
	{
		newlist = ft_lstnew(ft_itoa(index));
		ft_lstadd_front(&list, newlist);
		index++;
	}
	list = ft_lstlast(list);
	printf("%s\n", (char *)list->content);
}
*/