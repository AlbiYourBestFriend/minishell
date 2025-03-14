/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_here_doc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 16:03:58 by mleproux          #+#    #+#             */
/*   Updated: 2025/03/14 15:04:02 by tprovost         ###   ########.fr       */
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

static char	*get_limiter(char *cmd_line, int *i)
{
	char	*limiter;
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
	limiter = ft_substr(cmd_line, *i, len);
	(*i) += len;
	if (limiter == NULL)
		return (allocate_error(ALLOC_ERR), NULL);
	temp = limiter;
	limiter = handle_quotes(limiter);
	free(temp);
	return (limiter);
}

static int	handle_heredoc(t_data *data, t_command *cmd, int *i)
{
	char	*limiter;

	(*i) += 2;
	limiter = get_limiter(cmd->cmd_line, i);
	if (limiter == NULL)
		return (0);
	cmd->heredoc_fd = here_doc(data, cmd->heredoc_fd, limiter);
	free(limiter);
	if (cmd->heredoc_fd == -1)
		return (0);
	return (1);
}

int	read_heredoc(t_data *data)
{
	int			i;
	int			result;
	t_command	*temp;

	temp = data->commands;
	while (temp != NULL)
	{
		i = 0;
		result = 1;
		while (temp->cmd_line[i] != '\0')
		{
			if (check_token(temp->cmd_line, i) == 2)
				result = handle_heredoc(data, temp, &i);
			else if (temp->cmd_line[i] == '\''
				|| temp->cmd_line[i] == '\"')
				i = skip_quotes(temp->cmd_line, i);
			else if (temp->cmd_line[i] != '\0')
				i++;
			if (result == 0)
				return (0);
		}
		temp = temp->next;
	}
	return (1);
}
