/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:43:35 by mleproux          #+#    #+#             */
/*   Updated: 2025/02/25 13:35:13 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*env_var_write(t_data *data, char *arg, char *new_arg, int *index)
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
	if (name == NULL)
		return (NULL); // free le new_arg?
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

static char	*double_quote_write(t_data *data, char *arg, char *new_arg, int *index)
{
	index[0]++;
	while (arg[index[0]] != '\"' && arg[index[0]] != '\0')
	{
		if (arg[index[0]] == '$' && ft_isspace(arg[index[0] + 1]) == 0)
		{
			env_var_write(data, arg, new_arg, index);
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

static char	*single_quote_write(char *arg, char *new_arg, int *index)
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

char	*process_argument(t_data *data, char *arg, char *new_arg)
{
	int	index[2];

	index[0] = 0;
	index[1] = 0;
	while ((int)ft_strlen(arg) > index[0])
	{
		if (arg[index[0]] == '\'')
			new_arg = single_quote_write(arg, new_arg, index);
		else if (arg[index[0]] == '\"')
			new_arg = double_quote_write(data, arg, new_arg, index);
		else if (arg[index[0]] == '$' && ft_isspace(arg[index[0] + 1]) == 0)
			new_arg = env_var_write(data, arg, new_arg, index);
		else
		{
			new_arg[index[1]] = arg[index[0]];
			index[0]++;
			index[1]++;
		}
		if (new_arg == NULL)
			return (NULL);
	}
	new_arg[index[1]] = '\0';
	return (new_arg);
}

void	clean_args(t_data *data, t_command *cmd)
{
	char	*new_arg;
	int		i;
	int		len;

	len = 0;
	i = 0;
	while (cmd->args[i] != NULL)
	{
		len = arglen(data, cmd->args[i]);
		if (len == -1) // erreur
			return ;
		new_arg = malloc((len + 1) * sizeof(char));
		if (new_arg == NULL) // erreur
			return ;
		new_arg = process_argument(data, cmd->args[i], new_arg);
		if (new_arg == NULL) // erreur
			return ;
		free(cmd->args[i]);
		cmd->args[i] = NULL;
		cmd->args[i] = new_arg;
		i++;
	}
}
