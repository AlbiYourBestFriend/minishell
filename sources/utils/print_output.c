/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:43:35 by mleproux          #+#    #+#             */
/*   Updated: 2025/02/13 16:36:24 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	get_quote_type(char c)
{
	if (c == '\'')
		return ('\'');
	else if (c == '\"')
		return ('\"');
	else
		return ('\0');
}

static void	print_env_var(char *arg, int *i)
{
	char	var[MY_CHAR_MAX];
	int		j;

	j = 0;
	while (arg[(*i) + j] != ' ' && arg[(*i) + j] != '\0')
	{
		var[j] = arg[(*i) + j];
		j++;
	}
	var[j] = '\0';
	printf("my env var :%s\n", var);
}

static void	simple_quote_print(char *arg, int *i)
{
	(*i)++;
	while (arg[*i] != '\'' && arg[*i] != '\0')
	{
		write(1, &arg[*i], 1);
		(*i)++;
	}
	if (arg[*i] == '\'')
		(*i)++;
}

static void	double_quote_print(char *arg, int *i)
{
	(*i)++;
	while (arg[*i] != '\"' && arg[*i] != '\0')
	{
		if (arg[*i] == '$')
			print_env_var(arg, i);
		write(1, &arg[*i], 1);
		(*i)++;
	}
	if (arg[*i] == '\"')
		(*i)++;
}

void	print_output(t_command *cmd, int arg_i)
{
	int		i;
	char	quote_type;

	while (cmd->args[arg_i] != NULL)
	{
		i = 0;
		while (cmd->args[arg_i][i] != '\0')
		{
			quote_type = get_quote_type(cmd->args[arg_i][i]);
			if (quote_type == '\'')
				simple_quote_print(cmd->args[arg_i], &i);
			else if (quote_type == '\"')
				double_quote_print(cmd->args[arg_i], &i);
			else
			{
				write(1, &cmd->args[arg_i][i], 1);
				i++;
			}
		}
		arg_i++;
	}
}
