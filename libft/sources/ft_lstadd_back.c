/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 17:11:45 by mleproux          #+#    #+#             */
/*   Updated: 2025/01/13 11:14:53 by mleproux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	last = ft_lstlast(*lst);
	if (last)
		last->next = new;
	else
		*lst = new;
}
/*
int main(void)
{
    t_list *list;
    t_list *newlist;
    int index;

    list = ft_lstnew("0");
    index = 1;
    while (index < 5)
    {
        newlist = ft_lstnew(ft_itoa(index));
        ft_lstadd_front(&list, newlist);
        index++;
    }

    while (index < 10)
    {
        newlist = ft_lstnew(ft_itoa(index));
        ft_lstadd_back(&list, newlist);
        index++;
    }

    t_list *current = list;
    index = 0;
    while (index < 10)
    {
        printf("%s\n", (char *)current->content);
        current = current->next;
        index++;
    }
}
*/
