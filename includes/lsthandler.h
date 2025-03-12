/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lsthandler.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:24:55 by mleproux          #+#    #+#             */
/*   Updated: 2025/02/20 15:14:54 by mleproux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LSTHANDLER_H
# define LSTHANDLER_H

// structures

typedef struct s_command
{
	char				*cmd_line;
	char				**args;
	int					input_fd;
	int					output_fd;
	pid_t				pid;
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
t_command	*cmdnew(char *cmd_line);
void		cmdadd_back(t_command **lst, t_command *newlst);
t_command	*cmdlast(t_command *lst);
int			cmdsize(t_command *lst);

#endif
