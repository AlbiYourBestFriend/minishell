/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:26:03 by tprovost          #+#    #+#             */
/*   Updated: 2025/02/26 19:54:10 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	len_in_quote(char *str, int *i)
{
	char	quote;
	int		len;

	quote = str[*i];
	(*i)++;
	len = 0;
	while (str[*i] != quote && str[*i])
	{
		len++;
		(*i)++;
	}
	(*i)++;
	return (len);
}

static int	total_len(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '\"')
			len += len_in_quote(str, &i);
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

static void	put_in_quotes(char *new_arg, int *j, char *arg, int *i)
{
	char	c;

	c = arg[*i];
	(*i)++;
	while (arg[*i] != c)
	{
		new_arg[*j] = arg[*i];
		(*i)++;
		(*j)++;
	}
	(*i)++;
}

// n = 0 quand on appelle la fonction sinon elle fait plus de 25 lignes
int	handle_quotes(t_command *cmd, char **arg, int n)
{
	int		i;
	int		j;
	char	*new_arg;

	while (arg[n] != NULL)
	{
		new_arg = malloc((total_len(arg[n]) + 1) * sizeof(char));
		if (new_arg == NULL)
			return (0);
		i = 0;
		j = 0;
		while (arg[n][i] != '\0')
		{
			if (arg[n][i] == '\'' || arg[n][i] == '\"')
				put_in_quotes(new_arg, &j, arg[n], &i);
			else if (arg[n][i] != '\0')
			{
				new_arg[j] = arg[n][i];
				j++;
				i++;
			}
		}
		new_arg[j] = '\0';
		free(arg[n]);
		arg[n] = new_arg;
		n++;
	}
	cmd->args = arg;
	return (1);
}
