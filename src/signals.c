#include "../includes/minishell.h"

void	read_handler(int signal, siginfo_t *data, void *n_data)
{
    (void)signus;
    printf ("\n Ctrl-C: Deteniendo la ejecución. Volviendo al shell\n");
    exit(EXIT_SUCCESS);
}

void	exec_handler(int signal, siginfo_t *data, void *n_data)
{
    (void)signus;
    printf ("\n Ctrl-\\: Interrumpiendo la ejecución. Volviendo al shell\n");
    exit(EXIT_SUCCESS);
}

void	init_signals(int mode)
{
    signal(SIGINT, sigintHandler);
    signal(SIGQUIT, sigquitHandler);

}