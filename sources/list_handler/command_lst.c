/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:21:36 by mleproux          #+#    #+#             */
/*   Updated: 2025/02/13 16:44:34 by mleproux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_command	*cmdnew(char *cmd_line)
{
	t_command	*list;

	list = malloc(sizeof(t_command));
	if (!list)
		return (NULL);
	list->cmd_line = cmd_line;
	list->input_fd = 0;
	list->output_fd = 1;
	list->args = NULL;
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
