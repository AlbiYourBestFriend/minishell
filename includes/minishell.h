/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:50:18 by tprovost          #+#    #+#             */
/*   Updated: 2025/02/18 19:07:49 by tprovost         ###   ########.fr       */
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
# include <signal.h>

# define PROMPT "Minishell : "
# define MY_CHAR_MAX 4096

# include <dirent.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <curses.h>
# include <fcntl.h>
# include <sys/types.h>

// pipex errors
# define ENV_ERR		"no environment detected"
# define ARGC_ERR		"wrong number of argument"
# define HERE_DOC		"here_doc"
# define INFILE_ERR		"error in opening infile"
# define OUTFILE_ERR	"error in opening outfile"
# define PIPE_ERR		"error in pipe creation"
# define FORK_ERR		"error during fork"
# define DUP_ERR		"error when duplicate(1) fd"
# define DUP2_ERR		"error when duplicate(2) fd"
# define PATH			"PATH="
# define EXECVE_ERR		"error during execve"
# define PATH_ERR		"path not found"

// can be deleted ?
# define INPUT 1
# define HEREDOC 2
# define TRUNC 3
# define APPEND 4
# define PIPE 5

// builtins
// # define ECHO "echo"
# define CD "cd"
# define PWD "pwd"
# define EXPORT "export"
# define UNSET "unset"
# define ENV "env"
# define EXIT "exit"

# define HEREDOCFILE ".heredoc.tmp"

typedef struct s_data
{
	t_env_var	*env_variables;
	t_command	*commands;
}			t_data;

// pour connaitre le resultat des signaux et des execve
extern volatile int	g_exit_status;

// Builtins
void		root_return(t_data *data);
void		ft_cd(t_data *data, t_command *cmd);
void		ft_echo(t_data *data, t_command *cmd);
void		ft_env(t_data *data, t_command *cmd);
void		ft_exit(t_data *data, t_command *cmd);
void		ft_export(t_data *data, t_command *cmd);
void		ft_pwd(t_data *data);
void		ft_unset(t_data *data, t_command *cmd);

// Executing
void		ft_execute(t_data *data);
char		*create_path(char *path, char *cmd);
char		**get_paths(void);
int			execute_builtins(t_data *data, t_command *cmd);
int			check_if_builtins(t_command *cmd);
int			init_builtins(t_data *data, t_command *cmd);
void		signal_handler(int state);

// Parsing
int			check_quotes(char *cmd);
int			is_env_var(char *cmd);
int			exist_var(t_data *data, char *name);
t_env_var	*add_env_var(t_data *data, char *name, char *value);
t_env_var	*get_env_var(t_data *data, char *name);
int			skip_quote(char *cmd, int n, int s);
char		*get_env_var_name(char *cmd);
char		*get_env_var_value(char *cmd);
t_env_var	*modif_env_var(t_data *data, char *name, char *value, int n);
t_env_var	*handle_env_var(t_data *data, char *cmd, int n);
int			here_doc(int currentfd, char *limiter);
int			open_file(char *filename, int currentfd, int isoutput, int dotrunc);
int			read_redirection(t_command *cmd);

// Utils
int			check_token(char *str);
char		*clean_cmd(char *cmd);
char		**copy_tab(char **tab);
int			count_char(char *str, char c);
void		free_data(t_data *data);
void		free_env_var(t_env_var *env_var);
void		free_tab(char **tab);
t_data		init_data(char **env);
int			get_word_count(char *str);
char		*get_next_word(char *str, int *index);
char		**lst_to_tab(t_env_var *env_var);
void		print_error(char *msg);
void		print_output(t_command *cmd, int arg_index);
int			ft_check(char **tab, char *line, char c, int k);
char		**split_cmd_line(char *line, char c);
int			tab_len(char **tab);
void		free_cmds(t_data *data);

#endif
