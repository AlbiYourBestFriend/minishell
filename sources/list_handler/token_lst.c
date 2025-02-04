/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:26:56 by mleproux          #+#    #+#             */
/*   Updated: 2025/02/04 11:21:16 by mleproux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*tokennew(void)
{
	t_token	*list;

	list = malloc(sizeof(t_token));
	if (!list)
		return (NULL);
	list->next = NULL;
	return (list);
}

void	tokenadd_back(t_token **lst, t_token *newlst)
{
	t_token	*last;

	last = tokenlast(*lst);
	if (last)
		last->next = newlst;
	else
		*lst = newlst;
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