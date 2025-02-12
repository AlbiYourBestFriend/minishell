/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:05:52 by tprovost          #+#    #+#             */
/*   Updated: 2025/02/12 19:27:06 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	if (cmd[i] != '=')
		return (0);
	i++;
	if (cmd[i] == '\0' || ft_isspace(cmd[i]) == 1)
		return (-1);
	return (1);
}

t_env_var	*modif_env_var(t_data *data, char *name, char *value)
{
	t_env_var	*env_var;

	env_var = NULL;
	if (exist_var(data, name) == 0) // la variable d'environnement n'existe pas encore
	{
		if (value == NULL)
			env_var = add_env_var(data, ft_strdup(name), NULL);
		else
			env_var = add_env_var(data, ft_strdup(name), ft_strdup(value));
	}
	else // existe dans la liste chainee
	{
		env_var = get_env_var(data, name);
		if (env_var->value != NULL)
			free(env_var->value);
		if (value == NULL)
			env_var->value = NULL;
		else
			env_var->value = ft_strdup(value);
	}
	free(name);
	if (value != NULL)
		free(value);
	return (env_var);
}

void	handle_env_var(t_data *data, char *cmd, int n)
{
	char	*name;
	char	*value;

	if (n == 1)
	{
		name = get_env_var_name(cmd);
		value = get_env_var_value(cmd);
	}
	else if (n == -1)
	{
		name = get_env_var_name(cmd);
		value = NULL;
	}
	modif_env_var(data, name, value);
}

// int main(int argc, char **argv)
// {
// 	(void)argc;
// 	printf("%d\n", is_env_var(argv[1]));
// }
