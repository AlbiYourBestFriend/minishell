/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:08:49 by mleproux          #+#    #+#             */
/*   Updated: 2025/02/12 16:58:15 by mleproux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	handle_redirection(t_command *cmd, int redirection, int *index)
{
	char	*filename;

	filename = get_next_word(cmd->cmd_line, index);
	if (filename == NULL)
	{
		printf("c'est valo non");
		return (0);
	}
	printf("filename or limiter:%s\n", filename);
	if (check_token(filename) > 0)
		return (free(filename), 0); // syntax error near unexpected token
	if (redirection == INPUT)
		cmd->input_fd = open_file(filename, cmd->input_fd, 0, 0);
	else if (redirection == HEREDOC)
		cmd->input_fd = here_doc(cmd->input_fd, filename);
	else if (redirection == TRUNC)
		cmd->output_fd = open_file(filename, cmd->output_fd, 1, 1);
	else if (redirection == APPEND)
		cmd->output_fd = open_file(filename, cmd->output_fd, 1, 0);
	free(filename);
	return (1);
}

static char	*handle_argument(char *new_cmd_line, char *word)
{
	char	*temp;

	if (new_cmd_line == NULL)
		return (ft_strdup(word));
	temp = new_cmd_line;
	new_cmd_line = ft_strjoin(new_cmd_line, " ");
	if (new_cmd_line == NULL)
		return (free(temp), NULL);
	free(temp);
	temp = new_cmd_line;
	new_cmd_line = ft_strjoin(new_cmd_line, word);
	if (temp)
		free(temp);
	if (new_cmd_line == NULL)
		return (NULL);
	return (new_cmd_line);
}

static int	write_new_cmd_line(char **new_cmd_line, char *word)
{
	*new_cmd_line = handle_argument(*new_cmd_line, word);
	if (*new_cmd_line == NULL)
		return (0);
	return (1);
}
static int	insert_arguments(t_command *cmd, char *new_cmd_line)
{
	char	*word;
	int		index;
	int		arg_index;

	cmd->args = malloc(sizeof(char *) * get_word_count(new_cmd_line) + 1);
	cmd->cmd_line = new_cmd_line;
	index = 0;
	arg_index = 0;
	while (new_cmd_line[index] != '\0')
	{
		word = get_next_word(new_cmd_line, &index);
		if (word == NULL)
			return (0);
		cmd->args[arg_index] = word;
		arg_index++;
	}
	cmd->args[arg_index] = NULL;
	return (1);
}

int	read_redirection(t_command *cmd)
{
	char	*new_cmd_line;
	char	*word;
	int		index;
	int		redirection;

	index = 0;
	new_cmd_line = NULL;
	while (cmd->cmd_line[index] != '\0')
	{
		word = get_next_word(cmd->cmd_line, &index);
		if (word == NULL)
			return (0);
		redirection = check_token(word);
		if (redirection > 0 && redirection < 5)
		{
			if (handle_redirection(cmd, redirection, &index) == 0)
				return (free(word), 0);
		}
		else if (write_new_cmd_line(&new_cmd_line, word) == 0)
			return (free(word), 0);
		free(word);
	}
	if (insert_arguments(cmd, new_cmd_line))
		return (free(new_cmd_line), 0);
	return (1);
}
