/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:21:36 by mleproux          #+#    #+#             */
/*   Updated: 2025/02/26 18:49:09 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_cmds(t_data *data)
{
	t_command	*to_free;
	t_command	*temp;

	temp = data->commands;
	while (temp != NULL)
	{
		free_tab(temp->args);
		if (temp->cmd_line != NULL)
			free(temp->cmd_line);
		to_free = temp;
		temp = temp->next;
		to_free->next = NULL;
		free(to_free);
	}
	data->commands = NULL;
}

t_command	*cmdnew(char *cmd_line)
{
	t_command	*list;

	list = malloc(sizeof(t_command));
	if (list == NULL)
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
	if (last != NULL)
		last->next = newlst;
	else
		*lst = newlst;
}

t_command	*cmdlast(t_command *lst)
{
	t_command	*temp;

	if (lst == NULL)
		return (NULL);
	temp = lst;
	while (temp->next != NULL)
		temp = temp->next;
	return (temp);
}

int	cmdsize(t_command *lst)
{
	t_command	*temp;
	int			count;

	temp = lst;
	count = 0;
	while (temp != NULL)
	{
		count++;
		temp = temp->next;
	}
	return (count);
}
