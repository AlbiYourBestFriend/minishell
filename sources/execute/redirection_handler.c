/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:58:17 by mleproux          #+#    #+#             */
/*   Updated: 2025/02/10 15:38:10 by mleproux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_redirection(char *cmd, int index)
{
	int	current;
	
	if (cmd[index] == '<')
	{
		current = INPUT;
		if (cmd[index + 1] == cmd[index])
		{
			current = HEREDOC;
			if (cmd[index + 3] == cmd[index])
				return (0);	
		}
	}
	else if (cmd[index] == '>')
	{
		current = TRUNC;
		if (cmd[index + 1] == cmd[index])
		{
			current = APPEND;
			if (cmd[index + 3] == cmd[index])
				return (0);	
		}
	}
	return (current);
}

int	word_len(char *cmd, int index)
{
	int	len;
	
	len = 0;
	while (cmd[index + len] && cmd[index + len] != '\0' \
		&& ft_isspace(cmd[index + len] == 0))
	{
		len++;
	}
	return (len);
}
	
char	*get_next_word(char *cmd, int index)
{
	char	*word;
	int		len;

	word = malloc(sizeof(char *) * word_len(cmd, index) + 1);
	if (word == NULL)
		return (NULL);
	len = 0;
	while (cmd[index + len] && cmd[index + len] != '\0' \
		&& ft_isspace(cmd[index + len] == 0))
	{
		word[len] = cmd[index + len];
		len++; 
	}
	word[len] = '\0';
	return (word);
}

char *read_redirection(char *cmd)
{
	char	*filename;
	int		index;
	int		redirection;

	index = 0;
	while (cmd[index] != '\0')
	{
		redirection = get_redirection(cmd, index);
		if (redirection != 0)
		{
			if (redirection == INPUT || redirection == TRUNC)
				index++;
			else if (redirection == HEREDOC || redirection == APPEND)
				index += 2;
			filename = get_next_word(cmd, index);
			printf("redirection = %d\n filename = %s\n", redirection, filename);
		}
	}
}
