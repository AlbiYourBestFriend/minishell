/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:50:18 by tprovost          #+#    #+#             */
/*   Updated: 2025/02/06 13:41:31 by tprovost         ###   ########.fr       */
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

typedef struct s_data
{
	char				**env;
	struct s_command	*commands;
}			t_data;

// Main functions
int		parsing(t_data data, char *input);

// Utils
char	**copy_tab(char **tab);
int		tab_len(char **tab);
int	is_in_str(char *cmd, int i);
// char	*ft_clean_cmd(char *cmd);
char	**ft_clean_cmd(char *line, char c);
void	free_tab(char **tab);
t_data	init_data(char **env);
void	print_error(char *msg);

#endif
