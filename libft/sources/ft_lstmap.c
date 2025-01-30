/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 10:15:38 by mleproux          #+#    #+#             */
/*   Updated: 2024/10/28 13:25:48 by mleproux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlist;
	t_list	*temp;

	newlist = NULL;
	if (!lst)
		return (NULL);
	temp = NULL;
	while (lst)
	{
		temp = ft_lstnew(NULL);
		if (!temp)
		{
			ft_lstclear(&newlist, del);
			return (NULL);
		}
		temp->content = f(lst->content);
		ft_lstadd_back(&newlist, temp);
		lst = lst->next;
	}
	return (newlist);
}
/*
static void *toupper_func(void *s1)
{
    char *s2 = (char *)s1;
    char *new_str = malloc(strlen(s2) + 1);
    int index;

    if (!new_str)
        return (NULL);
    
    index = 0;
    while (s2[index] != '\0')
    {
        new_str[index] = ft_toupper(s2[index]);
        index++;
    }
    new_str[index] = '\0';
    return (new_str);
}

static void delete(void *poop)
{
	printf("%s\n", (char *)poop);
}

int	main(void)
{
	t_list	*list;

	list = ft_lstnew("bonjour");
	ft_lstadd_back(&list, ft_lstnew("les"));
	ft_lstadd_back(&list, ft_lstnew("amis"));
	
	t_list	*temp;
	temp = list;
	while (temp)
	{
		printf("%s\n", (char*)temp->content);
		temp = temp->next;
	}

	t_list	*newlist;
	newlist = ft_lstmap(list, toupper_func, delete);

	t_list	*temp2;
	temp2 = newlist;
	while (temp2)
	{
		printf("%s\n", (char*)temp2->content);
		temp2 = temp2->next;
	}
}
*/