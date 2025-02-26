/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:43:35 by mleproux          #+#    #+#             */
/*   Updated: 2025/02/25 17:28:35 by mleproux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*process_argument(t_data *data, char *arg, char *new_arg)
{
	int	index[2];

	index[0] = 0;
	index[1] = 0;
	printf("ARG=%s\n", arg);
	while ((int)ft_strlen(arg) > index[0])
	{
		if (arg[index[0]] == '\'')
			new_arg = single_quote_write(arg, new_arg, index);
		else if (arg[index[0]] == '\"')
			new_arg = double_quote_write(data, arg, new_arg, index);
		else if (arg[index[0]] == '$' && ft_isalpha(arg[index[0] + 1]) == 1)
			new_arg = env_var_write(data, arg, new_arg, index);
		else if (arg[index[0]] == '$' && arg[index[0] + 1] == '?')
			new_arg = exit_status_write(data, new_arg, index);
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
