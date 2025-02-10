/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lsthandler.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:24:55 by mleproux          #+#    #+#             */
/*   Updated: 2025/02/10 11:30:12 by mleproux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LSTHANDLER_H
# define LSTHANDLER_H

# define PIPE '|'

// structures
typedef struct s_token
{
	int				type;
	struct s_token	*next;
}			t_token;

typedef struct s_command
{
	char				*name;
	char				**args;
	struct s_command	*next;
}			t_command;

// functions
t_command	*cmdnew(char **args);
void		cmdadd_back(t_command **lst, t_command *newlst);
t_command	*cmdlast(t_command *lst);
t_token		*tokennew(void);
void		tokenadd_back(t_token **lst, t_token *newlst);
t_token		*tokenlast(t_token *lst);

#endif
