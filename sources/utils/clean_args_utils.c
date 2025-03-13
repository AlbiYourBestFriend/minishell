/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_args_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:00:16 by mleproux          #+#    #+#             */
/*   Updated: 2025/03/13 17:43:33 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*exit_status_write(char *new_arg, int *index)
{
	char	*exit_status;
	int		j;

	index[0] += 2;
	exit_status = ft_itoa(g_exit_status);
	if (exit_status == NULL)
		return (allocate_error(ALLOC_ERR), NULL);
	j = 0;
	while (exit_status[j] != '\0')
	{
		new_arg[index[1]] = exit_status[j];
		index[1]++;
		j++;
	}
	free(exit_status);
	return (new_arg);
}

char	*env_var_write(t_data *data, char *arg, char *new_arg, int *index)
{
	int			j;
	char		*name;
	t_env_var	*env_var;

	index[0]++;
	j = 0;
	while (arg[(index[0]) + j] != '\0' && ft_isspace(arg[index[0] + j]) == 0
		&& arg[index[0] + j] != '\"' && arg[index[0] + j] != '\'')
		j++;
	name = ft_substr(arg, index[0], j);
	if (name == NULL) // free le new_arg? free(new_arg);
		return (allocate_error(ALLOC_ERR), NULL);
	env_var = get_env_var(data, name);
	free(name);
	index[0] += j;
	if (env_var != NULL)
	{
		j = -1;
		while (env_var->value[++j] != '\0')
		{
			new_arg[index[1]] = env_var->value[j];
			index[1]++;
		}
	}
	return (new_arg);
}

char	*double_quote_write(t_data *data, char *arg, char *new_arg, int *index)
{
	index[0]++;
	while (arg[index[0]] != '\"' && arg[index[0]] != '\0')
	{
		if (arg[index[0]] == '$' && ft_isalpha(arg[index[0] + 1]) == 1)
		{
			env_var_write(data, arg, new_arg, index);
			if (new_arg == NULL)
				return (NULL);
		}
		else if (arg[index[0]] == '$' && arg[index[0] + 1] == '?')
		{
			exit_status_write(new_arg, index);
			if (new_arg == NULL)
				return (NULL);
		}
		else
		{
			new_arg[index[1]] = arg[index[0]];
			index[0]++;
			index[1]++;
		}
	}
	if (arg[index[0]] == '\"')
		index[0]++;
	return (new_arg);
}

char	*single_quote_write(char *arg, char *new_arg, int *index)
{
	index[0]++;
	while (arg[index[0]] != '\'' && arg[index[0]] != '\0')
	{
		new_arg[index[1]] = arg[index[0]];
		index[0]++;
		index[1]++;
	}
	if (arg[index[0]] == '\'')
		(index[0])++;
	return (new_arg);
}
