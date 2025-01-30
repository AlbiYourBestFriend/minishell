/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 10:29:12 by tprovost          #+#    #+#             */
/*   Updated: 2024/10/25 13:48:14 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*l;
	t_list	*next_tl;

	l = NULL;
	if (lst == NULL)
		return (NULL);
	while (lst != NULL)
	{
		next_tl = ft_lstnew(NULL);
		if (next_tl == NULL)
		{
			ft_lstclear(&l, del);
			return (NULL);
		}
		next_tl->content = f(lst->content);
		ft_lstadd_back(&l, next_tl);
		lst = lst->next;
	}
	return (l);
}
