/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:26:03 by tprovost          #+#    #+#             */
/*   Updated: 2025/02/27 13:19:14 by tprovost         ###   ########.fr       */
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

static void	put_in_quotes(char *new_arg, int *n, char *arg, int *j)
{
	char	c;

	c = arg[*j];
	(*j)++;
	while (arg[*j] != c)
	{
		new_arg[*n] = arg[*j];
		(*j)++;
		(*n)++;
	}
	(*j)++;
}

// n = 0 quand on appelle la fonction sinon elle fait plus de 25 lignes
char	*handle_quotes(char *arg_i)
{
	int		j;
	int		n;
	char	*new_arg;

	new_arg = malloc((total_len(arg_i) + 1) * sizeof(char));
	if (new_arg == NULL)
		return (NULL);
	j = 0;
	n = 0;
	while (arg_i[j] != '\0')
	{
		if (arg_i[j] == '\'' || arg_i[j] == '\"')
			put_in_quotes(new_arg, &n, arg_i, &j);
		else if (arg_i[j] != '\0')
		{
			new_arg[n] = arg_i[j];
			j++;
			n++;
		}
	}
	new_arg[j] = '\0';
	return (new_arg);
}
