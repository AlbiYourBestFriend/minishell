/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:08:49 by mleproux          #+#    #+#             */
/*   Updated: 2025/02/26 20:01:19 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	skip_quotes(char *cmd_line, int i)
{
	char	quote;

	quote = cmd_line[i];
	i++;
	while (cmd_line[i] != quote && cmd_line[i] != '\0')
		i++;
	if (cmd_line[i] == quote)
		i++;
	return (i);
}

static char *clean_file_name(t_data *data, char *temp)
{
	char	*file_args;
	char	*file_name;

	
	file_name = handle_dollar();
	if (!file_name)
		return (NULL);
	file_args = split_cmd_line(file_name, ' ');
	free(file_name);
	if (!file_args)
		return (printf("minishell: %s\n", ALLOC_ERR), NULL);
	else if (tab_len(file_args) != 1)
	{
		printf("%s: ambiguous redirect\n", temp);
		return (free_tab(file_args), free(temp), NULL);
	}
	free(temp);
	file_name = handle_quotes(file_args[0]);
	free_tab(file_args);
	// file_name = malloc(sizeof(char) * (arglen(data, temp) + 1));
	// if (file_name == NULL)
	// 	return (printf("minishell: %s\n", ALLOC_ERR), free(temp), NULL);
	// file_name = process_argument(data, temp, file_name);
	// if (file_name == NULL)
	// 	return (free(temp), NULL);
	return (file_name);
}

static char	*get_file_name(t_data *data, char *cmd_line, int *i)
{
	char	*temp;
	int		len;

	while (cmd_line[*i] != '\0' && ft_isspace(cmd_line[*i]) == 1)
		(*i)++;
	len = 0;
	while (cmd_line[(*i) + len] != '\0'
		&& check_token(cmd_line, (*i) + len) == 0
		&& ft_isspace(cmd_line[(*i) + len]) == 0)
	{
		if (cmd_line[(*i) + len] == '\'' || cmd_line[(*i) + len] == '\"')
			len += skip_quotes(cmd_line, (*i) + len) - ((*i) + len);
		else
			len++;
	}
	temp = ft_substr(cmd_line, *i, len);
	(*i) += len;
	if (temp == NULL)
		return (printf("minishell: %s\n", ALLOC_ERR), NULL);
	return (clean_file_name(data, temp));
}

static int	handle_redirection(t_data *data, t_command *cmd, int *i)
{
	char	*filename;
	int		redirection;
	int		start;

	start = (*i);
	redirection = check_token(cmd->cmd_line, *i);
	if (redirection == 1 || redirection == 3)
		(*i)++;
	(*i)++;
	filename = get_file_name(data, cmd->cmd_line, i);
	if (filename == NULL)
		return (0);
	blankify(cmd->cmd_line, start, *i);
	if (redirection == 1)
		cmd->input_fd = open_file(filename, cmd->input_fd, 0, 0);
	else if (redirection == 2)
		cmd->input_fd = here_doc(data, cmd->input_fd, filename);
	else if (redirection == 3)
		cmd->output_fd = open_file(filename, cmd->output_fd, 1, 1);
	else if (redirection == 4)
		cmd->output_fd = open_file(filename, cmd->output_fd, 1, 0);
	if (cmd->input_fd == -1 || cmd->output_fd == -1)
		return (printf("%s: No such a file or directory\n", \
						filename), free(filename), 0);
	return (free(filename), 1);
}

int	read_redirection(t_data *data, t_command *cmd)
{
	// char	*new_arg;
	char	**args;
	int		index;
	int		result;

	index = 0;
	result = 1;
	while (cmd->cmd_line[index] != '\0')
	{
		if (check_token(cmd->cmd_line, index) != 0)
			result = handle_redirection(data, cmd, &index);
		else if (cmd->cmd_line[index] == '\'' || cmd->cmd_line[index] == '\"')
			index = skip_quotes(cmd->cmd_line, index);
		else if (cmd->cmd_line[index] != '\0')
			index++;
		if (result == 0)
			return (0);
	}
	cmd->cmd_line = handle_dollars(data, cmd->cmd_line);
	if (cmd->cmd_line == NULL)
		return (0);
	args = split_cmd_line(cmd->cmd_line, ' ');
	if (args == NULL || handle_quotes(cmd, args, 0) == 0)
		return (0);
	return (1);
}
