/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:43:35 by mleproux          #+#    #+#             */
/*   Updated: 2025/02/12 17:02:17 by mleproux         ###   ########.fr       */
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

static void	print_env_var(char *arg, int *index)
{
	char var[MY_CHAR_MAX];
	int	index2;

	index2 = 0;
	while (arg[(*index) + index2] != ' ' && arg[(*index) + index2] != '\0')
	{
		var[index2] = arg[(*index) + index2];
		index2++;
	}
	var[index2] = '\0';
	printf("my env var :%s\n", var);
}

static void simple_quote_print(char *arg, int *index)
{
	(*index)++;
	while (arg[*index] != '\'' && arg[*index] != '\0')
	{
		write(1, &arg[*index], 1);
		(*index)++;
	}
	if (arg[*index] == '\'')
		(*index)++;
}

static void double_quote_print(char *arg, int *index)
{
	(*index)++;
	while (arg[*index] != '\"' && arg[*index] != '\0')
	{
		if (arg[*index] == '$')
			print_env_var(arg, index);
		write(1, &arg[*index], 1);
		(*index)++;
	}
	if (arg[*index] == '\"')
		(*index)++;
}

void	print_output(t_command *cmd, int arg_index)
{
	int		index;
	char	quote_type;

	while (cmd->args[arg_index] != NULL)
	{
		index = 0;
		while (cmd->args[arg_index][index] != '\0')
		{
			quote_type = get_quote_type(cmd->args[arg_index][index]);
			if (quote_type == '\'')
				simple_quote_print(cmd->args[arg_index], &index);
			else if (quote_type == '\"')
				double_quote_print(cmd->args[arg_index], &index);
			else
			{
				write(1, &cmd->args[arg_index][index], 1);
				index++;
			}
		}
		arg_index++;
	}
}
