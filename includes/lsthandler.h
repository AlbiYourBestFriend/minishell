/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lsthandler.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:24:55 by mleproux          #+#    #+#             */
/*   Updated: 2025/02/03 16:49:56 by mleproux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Token type
# define INPUT 1
# define HERE_DOC 2
# define APPEND 3
# define TRUNC 4
# define PIPE '|'

// structures
typedef	struct s_token
{
	int	type;
	struct s_token	*next;
}	t_token;

typedef struct s_command
{
	char				*name;
	char				**args;
	struct s_command	*next;
}			t_command;

// functions
t_command	*cmdnew(void *content, char **args);
void		cmdadd_back(t_command **lst, t_command *new);
t_command	*cmdlast(t_command *lst);
t_token		*tokennew(void *content);
void		tokenadd_back(t_token **lst, t_token *new);
t_token		*tokenlast(t_token *lst);

