/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:05:52 by tprovost          #+#    #+#             */
/*   Updated: 2025/03/20 14:53:42 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// -2 name but no value / no '='
// -1 name + value = NULL
// 0 is not an env var
// 1 env + value != NULL
int	is_env_var(char *cmd)
{
	int	i;

	i = 0;
	if ((cmd[i] >= 'A' && cmd[i] <= 'Z') || (cmd[i] >= 'a' && cmd[i] <= 'z')
		|| cmd[i] == '_')
		i++;
	else
		return (0);
	while (((cmd[i] >= 'A' && cmd[i] <= 'Z') || (cmd[i] >= 'a' && cmd[i] <= 'z')
			|| (cmd[i] >= '0' && cmd[i] <= '9') || cmd[i] == '_')
		&& cmd[i] != '\0' && cmd[i] != '=')
		i++;
	if (cmd[i] != '\0' && cmd[i] != '=')
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
		env_var = add_env_var(data, name, value);
	else
	{
		env_var = get_env_var(data, name);
		if (n != -2)
		{
			if (env_var->value != NULL)
				free(env_var->value);
			env_var->value = value;
		}
		else
			env_var->status = 1;
		free(name);
	}
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
