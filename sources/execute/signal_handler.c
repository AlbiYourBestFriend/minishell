/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprovost <tprovost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:11:46 by tprovost          #+#    #+#             */
/*   Updated: 2025/02/18 16:14:29 by tprovost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	handle_signal_readline(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		// g_exit_status = sig + 128;
	}
}

static void	handle_signal_here_doc(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		// rl_replace_line("", 0);
		// rl_redisplay();
		// g_exit_status = sig + 128;
	}
	if (sig == SIGQUIT)
	{
		write(1, "\b\b  \b\b", 6);
		// g_exit_status = sig + 128;
	}
}

static void	handle_signal_exec(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		// rl_redisplay();
		// g_exit_status = sig + 128;
	}
	else if (sig == 3)
	{
		printf("core dumped\n");
		// g_exit_status = sig + 128;
	}
}

// state indique ce qu'on est en train de faire
void	signal_handler(int	state)
{
	struct sigaction	s_sig_init;
	struct sigaction	s_sig_end;

	s_sig_init.sa_flags = SA_RESTART;
	s_sig_end.sa_flags = SA_RESTART;
	sigemptyset(&(s_sig_init.sa_mask));
	sigemptyset(&(s_sig_end.sa_mask));
	if (state == 0) // wait prompt readline -> new prompt
	{
		s_sig_init.sa_handler = handle_signal_readline;
		s_sig_end.sa_handler = SIG_IGN;
	}
	if (state == 1) // wait end heredoc -> end heredoc + free
	{
		s_sig_init.sa_flags = 0;
		s_sig_init.sa_handler = handle_signal_here_doc;
		s_sig_end.sa_handler = handle_signal_here_doc;
	}
	if (state == 2) // exec program -> stop exec
	{
		s_sig_init.sa_handler = handle_signal_exec;
		s_sig_end.sa_handler = handle_signal_exec;
	}
	sigaction(SIGQUIT, &s_sig_end, NULL);
	sigaction(SIGINT, &s_sig_init, NULL);
}
