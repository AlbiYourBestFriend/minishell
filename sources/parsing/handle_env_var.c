/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:05:52 by tprovost          #+#    #+#             */
/*   Updated: 2025/02/10 19:23:50 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
// #include <stdio.h>

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
	// i++;
	// if (cmd[i] == '\0')
	// 	return (0);
	return (1);
}

void	handle_env_var(t_data *data, char *cmd)
{
	char		*name;
	char		*value;
	t_env_var	*env_var;
	int			n;
	int			i;

	name = get_env_var_name(cmd);
	value = get_env_var_value(cmd);
	env_var = NULL;
	n = exist_var(data, name);
	if (n == 0) // la variable d'environnement n'existe pas encore
		add_env_var(name, value);
	if (n == 1) // existe dans la liste chainee des variables d'environnement mais pas dans l'environnement
	{
		env_var = get_env_var(name);
		if (env_var->value != NULL)
			free(env_var->value);
		env_var->value = get_env_var_value(cmd);
	}
	if (n == 2) // existe dans l'environnement
	{
		i = 0;
		name = ft_strjoin(name, "=");
		while (ft_strncmp(name, data->my_env[i], ft_strlen(name)) != 0)
			i++;
		free(data->my_env[i]);
		data->my_env[i] = ft_strjoin(name, value);
	}
	free(name);
	free(value);
}

// int main(int argc, char **argv)
// {
// 	(void)argc;
// 	printf("%d\n", is_env_var(argv[1]));
// }
