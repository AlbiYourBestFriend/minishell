/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:08:49 by mleproux          #+#    #+#             */
/*   Updated: 2025/03/28 11:51:03 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_input_errors(t_command *cmd, char *filename)
{
	if (access(filename, F_OK) == -1)
	{
		cmd->input_fd = -1;
		nofile_error(NO_FILE_DIR, filename);
		return (0);
	}
	if (access(filename, O_RDONLY) == -1)
	{
		cmd->input_fd = -1;
		nofile_error(NO_PERM, filename);
		return (0);
	}
	return (1);
}

void	open_in(t_command *cmd, int redirection, char *filename)
{
	if (cmd->input_fd > 1)
		ft_close(cmd, 1);
	if (redirection == 2)
	{
		if (cmd->heredoc_fd == -1)
		{
			cmd->input_fd = -1;
			return ;
		}
		cmd->input_fd = dup(cmd->heredoc_fd);
		if (cmd->input_fd == -1)
			ft_printf("%s Dup failed", ERROR);
		return ;
	}
	if (check_input_errors(cmd, filename) == 0)
		return ;
	cmd->input_fd = open(filename, O_RDONLY);
	if (cmd->input_fd == -1)
		nofile_error(FILE_ERR, filename);
}

void	open_out(t_command *cmd, int redirection, char *filename)
{
	if (cmd->output_fd > 1)
		ft_close(cmd, 2);
	if (access(filename, F_OK) == -1)
	{
		cmd->output_fd = open(filename, O_WRONLY | O_CREAT, 0644);
		if (cmd->output_fd == -1)
			nofile_error(FILE_ERR, filename);
		return ;
	}
	if (access(filename, W_OK | R_OK) == -1)
	{
		cmd->output_fd = -1;
		return (nofile_error(NO_PERM, filename));
	}
	if (redirection == 3)
		cmd->output_fd = open(filename, O_WRONLY | O_TRUNC);
	else
		cmd->output_fd = open(filename, O_WRONLY | O_APPEND);
	if (cmd->output_fd == -1)
		nofile_error(FILE_ERR, filename);
}

int	open_file(t_command *cmd, int redirection, char *filename)
{
	if (redirection == 1 || redirection == 2)
		open_in(cmd, redirection, filename);
	else if (redirection == 3 || redirection == 4)
		open_out(cmd, redirection, filename);
	if (cmd->input_fd == -1 || cmd->output_fd == -1)
		return (0);
	return (1);
}
