/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:05:52 by tprovost          #+#    #+#             */
/*   Updated: 2025/02/25 16:46:30 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// -2 name but no value
// -1 name + value = NULL
// 0 is not an env var
// 1 env + value != NULL
int	is_env_var(char *cmd)
{
	int	i;

	i = 0;
	if (cmd[i] > 32 && cmd[i] < 127)
		i++;
	else
		return (0);
	while (cmd[i] > 32 && cmd[i] < 127 && cmd[i] != '\0' && cmd[i] != '=')
		i++;
	if (cmd[i] <= 32 || cmd[i] >= 127)
		return (0);
	if (cmd[i] == '\0')
		return (-2);
	i++;
	if (cmd[i] == '\0')
		return (-1);
	return (1);
}

t_env_var	*modif_env_var(t_data *data, char *name, char *value, int n)
{
	t_env_var	*env_var;

	env_var = NULL;
	if (exist_var(data, name) == 0)
		env_var = add_env_var(data, ft_strdup(name), value);
	else
	{
		env_var = get_env_var(data, name);
		if (n != -2)
		{
			if (env_var->value != NULL)
				free(env_var->value);
			if (value == NULL)
				env_var->value = NULL;
			else
				env_var->value = ft_strdup(value);
		}
		else
			env_var->status = 1;
	}
	free(name);
	if (value != NULL)
		free(value);
	return (env_var);
}

t_env_var	*handle_env_var(t_data *data, char *cmd, int n)
{
	char	*name;
	char	*value;

	name = get_env_var_name(cmd);
	if (name == NULL)
		return (NULL);
	value = NULL;
	if (n == 1)
	{
		value = get_env_var_value(cmd);
		if (value == NULL)
			return (free(name), NULL);
	}
	return (modif_env_var(data, name, value, n));
}

// int main(int argc, char **argv)
// {
// 	(void)argc;
// 	printf("%d\n", is_env_var(argv[1]));
// }
