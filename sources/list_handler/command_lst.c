/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:21:36 by mleproux          #+#    #+#             */
/*   Updated: 2025/02/11 17:11:52 by mleproux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_command	*cmdnew(char **args)
{
	t_command	*list;
	int			index;

	if (!args)
		return (NULL);
	list = malloc(sizeof(t_command));
	if (!list)
		return (NULL);
	list->args = ft_calloc(sizeof(char *), tab_len(args) + 1);
	if (!list->args)
		return (free(list), NULL);
	index = 0;
	while (args[index])
	{
		list->args[index] = args[index];
		index++;
	}
	// list->name = args[0];
	list->next = NULL;
	return (list);
}

void	cmdadd_back(t_command **lst, t_command *newlst)
{
	t_command	*last;

	last = cmdlast(*lst);
	if (last)
		last->next = newlst;
	else
		*lst = newlst;
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
