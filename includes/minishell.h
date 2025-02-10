/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:50:18 by tprovost          #+#    #+#             */
/*   Updated: 2025/02/10 18:10:55 by mleproux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

// Libraries
# include "../libft/sources/libft.h"
# include "lsthandler.h"
# include "colors.h"

// Standard Libraries
# include <string.h>
# include <stdarg.h>
# include <limits.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>

# define PROMPT "Minishell : "
# define EXIT "exit"

# define ENV_ERR		"no environment detected"
# define ARGC_ERR		"wrong number of argument"
// # define HERE_DOC		"here_doc"
# define INFILE_ERR		"error in opening infile"
# define OUTFILE_ERR	"error in opening outfile"
# define PIPE_ERR		"error in pipe creation"
# define FORK_ERR		"error during fork"
# define DUP_ERR		"error when duplicate(1) fd"
# define DUP2_ERR		"error when duplicate(2) fd"
# define PATH			"PATH="
# define EXECVE_ERR		"error during execve"
# define PATH_ERR		"path not found"

# define INPUT 1
# define HEREDOC 2
# define TRUNC 3
# define APPEND 4

# define HEREDOCFILE ".heredoc.tmp"

typedef struct s_data
{
	char				**env;
	char				**env_variables; // ou liste chainee
	struct s_command	*commands;
}			t_data;

// Main functions
int		here_doc(int currentfd, char *limiter);
// int		open_infile_outfile(char **args);

// Builtins
void	ft_echo(void *arg);
void	ft_cd(void *arg);
void	ft_pwd(void *arg);
void	ft_export(void *arg);
void	ft_unset(void *arg);
void	ft_env(void *arg);
void	ft_exit(void *arg);
int		execute_builtins(char *command_name);
int		check_if_builtins(char *command_name);
char *read_redirection(char *cmd);

// Utils
char	*clean_cmd(char *cmd);
char	**copy_tab(char **tab);
void	free_tab(char **tab);
t_data	init_data(char **env);
void	print_error(char *msg);
char	**split_pipes_cmd_line(char *line);
int		ft_check(char **tab, char *line, char c, int k);
int		tab_len(char **tab);

#endif
