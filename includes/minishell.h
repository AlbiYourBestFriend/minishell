/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:50:18 by tprovost          #+#    #+#             */
/*   Updated: 2025/03/18 17:07:22 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// Libraries
# include "../libft/sources/libft.h"

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
# include <dirent.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <curses.h>
# include <sys/types.h>

# define PROMPT "Minishell$ "
# define HEREDOCFILE ".tmp/heredoc"
# define MY_CHAR_MAX 4096

// errors messages
# define ERROR			"Minishell: "
# define NO_FILE_DIR	"No such file or directory"
# define NO_DIR			"Not a directory"
# define ALLOC_ERR		"Cannot allocate memory"
# define INVALID_ID		"not a valid identifier"
# define FILE_ERR		"Error in opening file"
# define NO_PERM		"Permission denied"
# define UNEXPEC_EOF	"unexpected end of file"
# define PIPE_ERR		"error in pipe creation"
# define FORK_ERR		"error during fork"
# define DUP2_ERR		"error when duplicate(2) fd"
# define DUP_ERR		"error when duplicate(1) fd"
# define EXECVE_ERR		"error during execve"

// # define ENV_ERR		"no environment detected"
// # define ARGC_ERR		"wrong number of argument"

typedef struct s_command
{
	char				*cmd_line;
	char				**args;
	int					input_fd;
	int					output_fd;
	int					heredoc_fd;
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

typedef struct s_data
{
	t_env_var	*env_variables;
	t_command	*commands;
	char		**splitted_cmds;
	char		*program_path;
	char		*tmp_path;
	char		*username;
	int			count_line;
	int			exit_status;
}			t_data;

// pour connaitre le resultat des signaux et des execve
extern volatile int	g_exit_status;

// Builtins
void		root_return(t_data *data);
int			return_home_user(t_data *data);
void		cd_switch_pwd(t_data *data, t_env_var *env_var_pwd);
int			check_path_cd(t_data *data, t_env_var *tmp_env_pwd, \
							char **tab, char *cd_path);
t_env_var	*cd_add_pwd(t_data *data, char *name);
void		cd_rm_last(char *pwd);
int			cd_check_chdir(t_command *cmd, char *tmp);
void		ft_cd(t_data *data, t_command *cmd);
void		ft_echo(t_command *cmd);
void		ft_env(t_data *data, t_command *cmd);
void		ft_exit(t_data *data, t_command *cmd, int p);
void		compare_var(char **str1, char **str2);
int			assign_value(t_env_var *tmp_var, char **tab, int i);
int			ft_export(t_data *data, t_command *cmd);
void		ft_pwd(void);
void		ft_unset(t_data *data, t_command *cmd);

// Executing
int			check_if_builtins(t_command *cmd);
int			execute_builtins(t_data *data, t_command *cmd);
int			init_builtins(t_data *data, t_command *cmd);
void		fd_handler(t_command *cmd, int output, int input);
void		wait_for_all(t_data *data);
int			try_execute(char *path, t_env_var *env_var, \
						char **cmds, int n);
int			ft_execute(t_data *data);
int			is_executable(char *cmd);
void		exec_executable(t_data *data, t_command *cmd);
char		*create_path(char *path, char *cmd);
void		signal_handler(int state);

// Commandes listes
t_command	*cmdnew(char *cmd_line);
void		cmdadd_back(t_command **lst, t_command *newlst);
t_command	*cmdlast(t_command *lst);
int			cmdsize(t_command *lst);

// Parsing
int			check_quotes(char *cmd);
int			len_env_var_value(t_data *data, char *cmd, int *i, int n);
int			get_len_simple_quote(char *cmd, int *i, int n);
int			get_len_double_quote(t_data *data, char *cmd, int *i, int n);
int			put_exit_status(char *str, int *i_n);
int			put_env_var_value(t_data *data, char *cmd, char *str, int *i_n);
void		put_simple_quote(char *cmd, char *str, int *i_n);
int			put_double_quote(t_data *data, char *cmd, char *str, int *i_n);
char		*handle_dollars(t_data *data, char *cmd);
int			is_env_var(char *cmd);
int			exist_var(t_data *data, char *name);
t_env_var	*add_env_var(t_data *data, char *name, char *value);
t_env_var	*get_env_var(t_data *data, char *name);
int			skip_quote(char *cmd, int n, int s);
char		*get_env_var_name(char *cmd);
char		*get_env_var_value(char *cmd);
t_env_var	*modif_env_var(t_data *data, char *name, char *value, int n);
t_env_var	*handle_env_var(t_data *data, char *cmd, int n);
char		*handle_quotes(char *arg);
char		*open_here_doc_file(t_data *data, int *fd);
int			here_doc(t_data *data, int currentfd, char *limiter);
int			read_heredoc(t_data *data);
int			is_complete_cmd_line(char *cmd);
int			process_cmd_line(t_data *data, t_command *cmd);
char		*new_readline_join_cmd(t_data *data, char *cmd);
int			open_file(t_command *cmd, int redirection, char *filename);
int			read_redirection(t_data *data, t_command *cmd);
char		*token_error(char *cmd);

// Utils
int			exit_status_len(int *i);
int			arglen(t_data *data, char *arg);
void		blankify(char *str, int start, int len);
void		clean_args(t_data *data, t_command *cmd);
char		*process_argument(t_data *data, char *arg, char *new_arg);
char		*single_quote_write(char *arg, char *new_arg, int *index);
char		*double_quote_write(t_data *data, char *arg, \
									char *new_arg, int *index);
char		*env_var_write(t_data *data, char *arg, char *new_arg, int *index);
int			check_token(char *cmd_line, int i);
char		*exit_status_write(char *new_arg, int *index);
char		*env_var_write(t_data *data, char *arg, char *new_arg, int *index);
char		*double_quote_write(t_data *data, \
								char *arg, char *new_arg, int *index);
char		*single_quote_write(char *arg, char *new_arg, int *index);
char		*process_argument(t_data *data, char *arg, char *new_arg);
char		*clean_cmd(char *cmd);
void		copy_and_inc(char *str1, int *i, char *str2, int *j);
char		**copy_tab(char **tab);
int			count_char(char *str, char c);
void		free_cmds(t_data *data);
void		free_data(t_data *data);
void		free_env_var(t_env_var *env_var);
void		free_tab(char **tab);
void		ft_free_all_exit(t_data *data, int exit_status);
int			ft_is_atol(char *str);
t_data		init_data(char **env, char *filelocation);
void		get_program_path(t_data *data, char *argv0);
int			get_word_count(char *str);
char		*get_next_word(char *str, int *index);
char		**lst_to_tab(t_env_var *env_var);
void		allocate_error(char *err);
void		nofile_error(char *err, char *filename);
int			ft_check(char **tab, char *line, char c, int k);
char		**split_cmd_line(char *line, char c);
int			tab_len(char **tab);
void		unlink_tmp(t_data *data);

#endif
