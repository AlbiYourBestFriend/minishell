/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:08:49 by mleproux          #+#    #+#             */
/*   Updated: 2025/02/21 13:27:30 by mleproux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	handle_redirection(t_data *data, t_command *cmd, char **args, int *index)
{
	char	*filename;
	int		redirection;

	redirection = check_token(args[(*index)]);
	(*index)++;
	filename = args[(*index)];
	if (filename == NULL)
	{
		printf("c'est valo non");
		return (0);
	}
	(*index)++;
	if (check_token(filename) > 0)
		return (free(filename), 0); // syntax error near unexpected token
	if (redirection == INPUT)
		cmd->input_fd = open_file(filename, cmd->input_fd, 0, 0);
	else if (redirection == HEREDOC)
		cmd->input_fd = here_doc(data, cmd->input_fd, filename);
	else if (redirection == TRUNC)
		cmd->output_fd = open_file(filename, cmd->output_fd, 1, 1);
	else if (redirection == APPEND)
		cmd->output_fd = open_file(filename, cmd->output_fd, 1, 0);
	return (1);
}

static int	count_args(char **args)
{
	int	index;
	int	count;

	index = 0;
	count = 0;
	while (args[index])
	{
		if (check_token(args[index]) > 0 && check_token(args[index]) < 5)
			index += 2;
		else
		{
			index++;
			count++;
		}
	}
	return (count);
}

static int	insert_arguments(t_command *cmd, char **args)
{
	int	index;
	int	args_index;

	cmd->args = malloc(sizeof(char *) * (count_args(args) + 1));
	if (!cmd->args)
		return (0);
	index = 0;
	args_index = 0;
	while (args[index])
	{
		if (check_token(args[index]) > 0 && check_token(args[index]) < 5)
			index += 2;
		else
		{
			cmd->args[args_index] = ft_strdup(args[index]);
			if (!cmd->args[args_index])
				return (0);
			index++;
			args_index++;
		}
	}
	cmd->args[args_index] = NULL;
	return (1);
}

int	read_redirection(t_data *data, t_command *cmd)
{
	char	**args;
	int		index;

	args = split_cmd_line(cmd->cmd_line, ' ');
	if (!args)
		return (0);
	index = 0;
	while (args[index])
	{
		if (check_token(args[index]) > 0 && check_token(args[index]) < 5)
		{
			if (handle_redirection(data, cmd, args, &index) == 0)
				return (free_tab(args), 0);
		}
		else
			index++;
	}
	if (!insert_arguments(cmd, args))
		return (free_tab(args), 0);
	free_tab(args);
	clean_args(data, cmd);
	return (1);
}
