#include "../includes/minishell.h"

void	read_handler(int signal, siginfo_t *data, void *n_data)
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
    else if (signal == SIGQUIT)
	{
		ft_putstr_fd("Quit: 3\n", STDERR_FILENO);
        rl_on_new_line();
		rl_replace_line("", 1);
	}
}

void	heredoc_handler(int signal, siginfo_t *data, void *n_data)
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

void	exec_handler(int signal, siginfo_t *data, void *n_data)
{
	(void) data;
	(void) n_data;
	if (signal == SIGINT)
	{
		ft_putstr_fd("\n", STDERR_FILENO);
		rl_replace_line("", 1);
	}
	else if (signal == SIGQUIT)
	{
		ft_putstr_fd("Quit: 3\n", STDERR_FILENO);
		rl_replace_line("", 1);
	}
	return ;
}

void eof_handler(int signal)
{
    if (signal == SIGQUIT)
    {
        ft_putstr_fd("Exit\n", STDERR_FILENO);
        exit(EXIT_SUCCESS); // O cualquier otro comportamiento que desees
    }
}

void	init_signals(int mode)
{
	struct sigaction	sign;

	sign.sa_flags = SA_RESTART;
	sigemptyset(&sign.sa_mask);
	if (mode == READ)
	{
		sign.sa_sigaction = read_handler;
		signal(SIGQUIT, SIG_IGN);
		sigaction(SIGINT, &sign, NULL);
	}
	else if (mode == HEREDOC)
	{
		sign.sa_sigaction = heredoc_handler;
		signal(SIGQUIT, SIG_IGN);
		sigaction(SIGINT, &sign, NULL);
	}
	else if (mode == EXEC)
	{
		sign.sa_sigaction = exec_handler;
		sigaction(SIGINT, &sign, NULL);
		sigaction(SIGQUIT, &sign, NULL);
	}
	else if (mode == EOF_MODE) // Modo para manejar EOF
    {
        signal(SIGQUIT, eof_handler); // Manejador específico para EOF
    }
}
