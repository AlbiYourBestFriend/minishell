/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 10:45:58 by tprovost          #+#    #+#             */
/*   Updated: 2025/02/26 13:25:21 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*check_name_redirection(char *cmd, int *i)
{
	while (ft_isspace(cmd[*i]) == 1)
		(*i)++;
	if (cmd[*i] == '\0')
		return ("newline");
	else if (cmd[*i] == '|')
		return ("|");
	else if (cmd[*i] == '<')
		return ("<");
	else if (cmd[*i] == '>')
		return (">");
	return (NULL);
}

static char	*check_redirection(char *cmd, int *i)
{
	char	c;

	if (cmd[*i] == '<' || cmd[*i] == '>')
	{
		c = cmd[*i];
		(*i)++;
		if (cmd[*i] == '<' || cmd[*i] == '>')
		{
			if (cmd[*i] != c && cmd[*i] == '<')
				return ("<");
			(*i)++;
			if (cmd[*i] == '<')
				return ("<");
			if (cmd[*i] == '>')
				return (">");
		}
		return (check_name_redirection(cmd, i));
	}
	return (NULL);
}

static char	*incorrect_redirection(char *cmd)
{
	int		i;
	char	*token;

	i = 0;
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '\'' || cmd[i] == '\"')
			i = skip_quote(cmd, i, 1);
		else
		{
			token = check_redirection(cmd, &i);
			if (token != NULL)
				return (token);
		}
		if (cmd[i] != '\0')
			i++;
	}
	return (NULL);
}

char	*token_error(char *cmd)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (cmd[i] != '\0' && ft_isspace(cmd[i]) == 1)
		i++;
	if (cmd[i] == '|')
		return ("|");
	i = 0;
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '|' && c == 0)
			c = 1;
		else if (cmd[i] != '|' && ft_isspace(cmd[i]) == 0)
			c = 0;
		else if (cmd[i] == '|' && c == 1)
			return ("|");
		if (cmd[i] == '\'' || cmd[i] == '\"')
			i = skip_quote(cmd, i, 1);
		if (cmd[i] != '\0')
			i++;
	}
	return (incorrect_redirection(cmd));
}
