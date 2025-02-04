/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:21:36 by mleproux          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/02/04 11:20:38 by mleproux         ###   ########.fr       */
=======
/*   Updated: 2025/02/03 19:28:39 by tprovost         ###   ########.fr       */
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_command	*cmdnew(char **args)
{
	t_command	*list;
	int			index;

<<<<<<< HEAD
	if (!args)
=======
	content = NULL;
	if (!arg)
>>>>>>> main
		return (NULL);
	list = malloc(sizeof(t_command));
	if (!list)
		return (NULL);
	list->args = ft_calloc(sizeof(char *), array_len(args));
	if (!list->args)
		return (free(list), NULL);
	index = 1;
<<<<<<< HEAD
	while (args[index])
	{
		list->args[index - 1] = args[index];
		index++;
	}	
	list->name = args[0];
=======
	// while ()
	// {
	// 	/* code */
	// }
	list->name = NULL;
	list->args = NULL;
>>>>>>> main
	list->next = NULL;
	return (list);
}

void	cmdadd_back(t_command **lst, t_command *newlst)
{
	t_command	*last;

<<<<<<< HEAD
	last = cmdlast(*lst);
=======
	last = NULL;
	// last = ft_lstlast(*lst);
>>>>>>> main
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
