/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:21:36 by mleproux          #+#    #+#             */
/*   Updated: 2025/02/03 16:52:00 by mleproux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_command	*cmdnew(void *content, char **arg)
{
	t_command	*list;
	int	index;

	if (!arg)
		return (NULL);
	list = malloc(sizeof(t_command));
	if (!list)
		return (NULL);
	list->args = malloc(sizeof(char *) * array_len(arg));
	if (!list->args)
		return (free(list), NULL);
	index = 1;
	while ()
	{
		/* code */
	}
	
	list->name = NULL;
	list->args = NULL;
	list->next = NULL;
	return (list);
}

void	cmdadd_back(t_command **lst, t_command *new)
{
	t_command	*last;

	last = ft_lstlast(*lst);
	if (last)
		last->next = new;
	else
		*lst = new;
}

t_command	*cmdlast(t_command *lst)
{
	t_command	*temp;

	if (!lst)
		return (NULL);
	temp = lst;
	while (temp->next != NULL)
		temp = temp->next;
	return (temp);
}