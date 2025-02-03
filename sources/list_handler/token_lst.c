/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:26:56 by mleproux          #+#    #+#             */
/*   Updated: 2025/02/03 18:00:40 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*tokennew(void *content)
{
	t_token	*list;

	content = NULL;
	list = malloc(sizeof(t_token));
	if (!list)
		return (NULL);
	list->next = NULL;
	return (list);
}

void	tokenadd_back(t_token **lst, t_token *new)
{
	t_token	*last;

	last = NULL;
	// last = ft_lstlast(*lst);
	if (last)
		last->next = new;
	else
		*lst = new;
}

t_token	*tokenlast(t_token *lst)
{
	t_token	*temp;

	if (!lst)
		return (NULL);
	temp = lst;
	while (temp->next != NULL)
		temp = temp->next;
	return (temp);
}