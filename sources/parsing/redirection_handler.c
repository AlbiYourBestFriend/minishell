/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:08:49 by mleproux          #+#    #+#             */
/*   Updated: 2025/03/13 11:50:26 by mleproux         ###   ########.fr       */
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

static char	*clean_file_name(t_data *data, char *temp)
{
	char	*file_name;
	char	**file_args;

	file_name = handle_dollars(data, temp);
	if (file_name == NULL)
		return (NULL);
	file_args = split_cmd_line(file_name, ' ');
	free(file_name);
	if (file_args == NULL)
		return (allocate_error(ALLOC_ERR), NULL);
	else if (tab_len(file_args) != 1)
	{
		printf("%s%s: ambiguous redirect\n", ERREUR, temp);
		return (free_tab(file_args), free(temp), NULL);
	}
	free(temp);
	file_name = handle_quotes(file_args[0]);
	free_tab(file_args);
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
		return (printf("%s%s\n", ERREUR, ALLOC_ERR), NULL);
	return (clean_file_name(data, temp));
}

static int	handle_redirection(t_data *data, t_command *cmd, int *i)
{
	char	*filename;
	int		redirection;
	int		start;

	start = (*i);
	redirection = check_token(cmd->cmd_line, *i);
	if (redirection == 2 || redirection == 4)
		(*i)++;
	(*i)++;
	filename = get_file_name(data, cmd->cmd_line, i);
	if (filename == NULL)
		return (0);
	blankify(cmd->cmd_line, start, *i);
	if (open_file(cmd, redirection, filename) == 0)
		return (free(filename), 0);
	return (free(filename), 1);
}

int	read_redirection(t_data *data, t_command *cmd)
{
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
	return (1);
}
