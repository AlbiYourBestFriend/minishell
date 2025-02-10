/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:08:49 by mleproux          #+#    #+#             */
/*   Updated: 2025/02/10 18:10:24 by mleproux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_redirection(char *word)
{
	int	redirection;

	if (word == NULL)
		return (-1);
	redirection = 0;
	if (ft_strncmp(word, "<", INT_MAX) == 0)
		redirection = INPUT;
	else if (ft_strncmp(word, "<<", INT_MAX) == 0)
		redirection = HEREDOC;
	else if (ft_strncmp(word, ">", INT_MAX) == 0)
		redirection = TRUNC;
	else if (ft_strncmp(word, ">>", INT_MAX) == 0)
		redirection = APPEND;
	free(word);
	return (redirection);
}

char	*read_redirection(char *cmd)
{
	char	*filename;
	int		index;
	int		redirection;

	index = 0;
	while (cmd[index] != '\0')
	{
		redirection = check_redirection(get_next_word(cmd, &index));
		if (redirection > 0)
		{
			filename = get_next_word(cmd, &index);
			if (filename == NULL)
				return (NULL);
			printf("%d -- %s\n", redirection, filename);
		}
	}
	return (NULL);
}


// ft_redirection()
// {
// 	extraire redirection
// 	return chaine sans redirection
// }