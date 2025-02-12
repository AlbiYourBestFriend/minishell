/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:05:52 by tprovost          #+#    #+#             */
/*   Updated: 2025/02/12 11:11:39 by mleproux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	handle_env(t_data *data, char *name, char *value)
{
	int		i;
	char	*tmp;

	i = 0;
	while (ft_strncmp(name, data->my_env[i], ft_strlen(name)) != 0
		&& data->my_env[i][ft_strlen(name)] != '='
		&& data->my_env[i] != NULL)
		i++;
	if (data->my_env[i] != NULL)
	{
		free(data->my_env[i]);
		tmp = ft_strjoin(name, "=");
		data->my_env[i] = ft_strjoin(tmp, value);
		free(tmp);
	}
}

void	modif_env_var(t_data *data, char *cmd)
{
	char		*name;
	char		*value;
	t_env_var	*env_var;
	int			n;

	name = get_env_var_name(cmd);
	value = get_env_var_value(cmd);
	env_var = NULL;
	n = exist_var(data, name);
	if (n == 0) // la variable d'environnement n'existe pas encore
		add_env_var(data, ft_strdup(name), ft_strdup(value));
	if (n == 1 || n == 3) // existe dans la liste chainee
	{
		env_var = get_env_var(data, name);
		if (env_var->value != NULL)
			free(env_var->value);
		env_var->value = ft_strdup(value);
	}
	if (n == 2 || n == 3) // existe dans l'environnement
		handle_env(data, name, value);
	free(name);
	free(value);
}

// void	handle_env_var(t_data *data, char *cmd)
// {

// }

// int main(int argc, char **argv)
// {
// 	(void)argc;
// 	printf("%d\n", is_env_var(argv[1]));
// }
