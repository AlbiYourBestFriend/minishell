/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_executable.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:55:23 by tprovost          #+#    #+#             */
/*   Updated: 2025/03/13 17:42:54 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_executable(char *cmd)
{
	if (cmd == NULL)
		return (0);
	if (cmd[0] != '.')
		return (0);
	if (cmd[1] != '/')
		return (0);
	if (cmd[2] <= 32 || cmd[2] >= 127)
		return (0);
	return (1);
}

static void	exec_executable_utils(t_data *data, t_command *cmd, t_env_var *tmp)
{
	int		i;
	char	*path;
	char	**tab;

	i = 1;
	if (ft_strlen(tmp->value) - i > 0
		&& tmp->value[ft_strlen(tmp->value) - i] == '/')
		i++;
	path = ft_strjoin(tmp->value, &(cmd->args[0][i]));
	if (path == NULL)
	{
		allocate_error(ALLOC_ERR);
		ft_free_all_exit(data, 1);
	}
	if (access(path, F_OK | X_OK) == 0)
	{
		tab = lst_to_tab(data->env_variables);
		if (tab == NULL) // a gerer
			return ;
		execve(path, cmd->args, tab);
		free_tab(tab);
	}
	free(path);
}

void	exec_executable(t_data *data, t_command *cmd)
{
	t_env_var	*tmp;

	if (try_execute(&cmd->args[0][1], \
	data->env_variables, cmd->args, 0) == 0)
	{
		ft_free_all_exit(data, 1);
	}
	tmp = get_env_var(data, "PWD");
	if (tmp == NULL)
	{
		printf("pwd not found\n");
		ft_free_all_exit(data, 1);
	}
	exec_executable_utils(data, cmd, tmp);
	printf("%s%s: %s\n", ERROR, cmd->args[0], NO_FILE_DIR);
	ft_free_all_exit(data, 1);
}
