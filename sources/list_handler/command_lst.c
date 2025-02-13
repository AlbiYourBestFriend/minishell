/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:21:36 by mleproux          #+#    #+#             */
/*   Updated: 2025/02/13 15:23:33 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_command	*cmdnew(char **args)
{
	t_command	*list;
	int			i;

	if (!args)
		return (NULL);
	list = malloc(sizeof(t_command));
	if (!list)
		return (NULL);
	list->args = ft_calloc(sizeof(char *), tab_len(args) + 1);
	if (!list->args)
		return (free(list), NULL);
	i = 0;
	while (args[i])
	{
		list->args[i] = args[i];
		i++;
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
