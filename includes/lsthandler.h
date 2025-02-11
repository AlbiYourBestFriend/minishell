/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lsthandler.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:24:55 by mleproux          #+#    #+#             */
/*   Updated: 2025/02/11 13:02:05 by tprovost         ###   ########.fr       */
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
	char				*name; // cmd line
	char				**args;
	int					input_fd;
	int					output_fd;
	struct s_command	*next;
}			t_command;

typedef struct s_env_var
{
	char				*name;
	char				*value;
	int					status;
	struct s_env_var	*next;
}			t_env_var;

// functions
t_command	*cmdnew(char **args);
void		cmdadd_back(t_command **lst, t_command *newlst);
t_command	*cmdlast(t_command *lst);
t_token		*tokennew(void);
void		tokenadd_back(t_token **lst, t_token *newlst);
t_token		*tokenlast(t_token *lst);

#endif
