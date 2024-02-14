#include "../includes/minishell.h"

void	sigintHandler(int signus)
{
    (void)signus;
    printf ("\n Ctrl-C: Deteniendo la ejecución. Volviendo al shell\n");
    exit(EXIT_SUCCESS);
}

void	sigquitHandler(int signus)
{
    (void)signus;
    printf ("\n Ctrl-\\: Interrumpiendo la ejecución. Volviendo al shell\n");
    exit(EXIT_SUCCESS);
}

void    init_signals(void)
{
    signal(SIGINT, sigintHandler);
    signal(SIGQUIT, sigquitHandler);

}