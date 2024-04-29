/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseivane <oseivane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:35:51 by oseivane          #+#    #+#             */
/*   Updated: 2024/04/29 14:35:52 by oseivane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	update_signal(t_env *env)
{
	// if (g_exit_sig)
	// 	env->end_type = g_exit_sig;
	(void)env;
}

static void	read_handler(int signal, siginfo_t *data, void *n_data)
{
	(void) data;
	(void) n_data;
	if (signal == SIGINT)
	{
		g_exit_sig = 1;
		ft_putstr_fd("\n", STDERR_FILENO);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

static void	heredoc_handler(int signal, siginfo_t *data, void *n_data)
{
	(void) data;
	(void) n_data;
	if (signal == SIGINT)
	{
		ft_putstr_fd("\n", STDERR_FILENO);
		rl_replace_line("", 1);
		exit(1);
	}
}

static void	exec_handler(int signal, siginfo_t *data, void *n_data)
{
	(void) data;
	(void) n_data;
	if (signal == SIGINT)
	{
		g_exit_sig = 130;
		ft_putstr_fd("\n", STDERR_FILENO);
		rl_replace_line("", 1);
	}
	else if (signal == SIGQUIT)
	{
		g_exit_sig = 131;
		ft_putstr_fd("Quit: 3\n", STDERR_FILENO);
		rl_replace_line("", 1);
	}
}

void	init_signals(int mode)
{
	struct sigaction	sig;

	sig.sa_flags = SA_RESTART;
	sigemptyset(&sig.sa_mask);
	g_exit_sig = 0;
	if (mode == READ)
	{
		sig.sa_sigaction = read_handler;
		signal(SIGQUIT, SIG_IGN);
		sigaction(SIGINT, &sig, NULL);
	}
	else if (mode == HEREDOC)
	{
		sig.sa_sigaction = heredoc_handler;
		signal(SIGQUIT, SIG_IGN);
		sigaction(SIGINT, &sig, NULL);
	}
	else if (mode == EXEC)
	{
		sig.sa_sigaction = exec_handler;
		sigaction(SIGINT, &sig, NULL);
		sigaction(SIGQUIT, &sig, NULL);
	}
}
