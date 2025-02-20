/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:43:35 by mleproux          #+#    #+#             */
/*   Updated: 2025/02/20 18:13:01 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	print_env_var(t_data *data, char *arg, int i)
{
	int			j;
	char		*name;
	t_env_var	*env_var;

	j = 0;
	while (arg[i + j] != '\0' && ft_isspace(arg[i + j]) == 0)
	{
		j++;
	}
	name = malloc((j + 1) * sizeof(char));
	j = 0;
	while (arg[i + j] != '\0' && ft_isspace(arg[i + j]) == 0)
	{
		name[j] = arg[i + j];
		j++;
	}
	name[j] = '\0';
	env_var = get_env_var(data, name);
	if (env_var != NULL)
		ft_putstr_fd(env_var->value, 1);
	free(name);
	return (j);
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

static void	double_quote_print(t_data *data, char *arg, int *i)
{
	(*i)++;
	while (arg[*i] != '\"' && arg[*i] != '\0')
	{
		if (arg[*i] == '$')
			(*i) = (*i) + 1 + print_env_var(data, arg, *i + 1);
		if (arg[(*i)] != '\0')
		{
			write(1, &arg[*i], 1);
			(*i)++;
		}
	}
	if (arg[*i] == '\"')
		(*i)++;
}

void	print_output(t_data *data, t_command *cmd, int arg_i)
{
	int		i;

	while (cmd->args[arg_i] != NULL)
	{
		i = 0;
		while (cmd->args[arg_i][i] != '\0')
		{
			if (cmd->args[arg_i][i] == '\'')
				simple_quote_print(cmd->args[arg_i], &i);
			else if (cmd->args[arg_i][i] == '\"')
				double_quote_print(data, cmd->args[arg_i], &i);
			else if (cmd->args[arg_i][i] == '$')
				i = i + 1 + print_env_var(data, cmd->args[arg_i], i + 1);
			else
			{
				write(1, &cmd->args[arg_i][i], 1);
				i++;
			}
		}
		arg_i++;
		if (cmd->args[arg_i])
			write(1, " ", 1);
	}
}
