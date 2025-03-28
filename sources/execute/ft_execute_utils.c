/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:55:36 by tprovost          #+#    #+#             */
/*   Updated: 2025/03/28 11:51:03 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	fd_handler(t_command *cmd, int output, int input)
{
	if (cmd->output_fd == 1 && cmd->output_fd != output)
	{
		cmd->output_fd = output;
		if (cmd->next && cmd->next->input_fd == 0)
			cmd->next->input_fd = input;
	}
	else if (cmd->output_fd != 1 && cmd->next == NULL)
		cmd->output_fd = output;
}

void	wait_for_all(t_data *data)
{
	t_command	*temp;
	int			status;

	status = 0;
	temp = data->commands;
	while (temp != NULL)
	{
		waitpid(temp->pid, &status, 0);
		g_exit_status = WEXITSTATUS(status);
		temp = temp->next;
	}
}

static void	command_executor_utils_2(t_data *data, t_command *cmd)
{
	char	**tab;

	if (access(cmd->args[0], X_OK) == 0)
	{
		tab = lst_to_tab(data->env_variables);
		if (tab == NULL)
			free_all_exit(data, g_exit_status);
		execve(cmd->args[0], cmd->args, tab);
		g_exit_status = 127;
		free_tab(tab);
	}
	else
		ft_printf("%s%s: %s\n", ERROR, cmd->args[0], NO_PERM);
}

char	*command_executor_utils(t_data *data, t_command *cmd)
{
	t_env_var	*tmp;

	if (cmd->args[0][0] == '/'
		&& try_execute(cmd->args[0], data->env_variables, cmd->args) == 1)
	{
		ft_printf("%s%s: command not found\n", ERROR, cmd->args[0]);
		g_exit_status = 127;
		free_all_exit(data, g_exit_status);
	}
	tmp = get_env_var(data, "PATH");
	if (tmp == NULL || tmp->value == NULL)
	{
		if (access(cmd->args[0], F_OK) == 0)
		{
			command_executor_utils_2(data, cmd);
		}
		else
			ft_printf("%s%s: %s\n", ERROR, cmd->args[0], NO_FILE_DIR);
		g_exit_status = 127;
		free_all_exit(data, g_exit_status);
	}
	return (tmp->value);
}
