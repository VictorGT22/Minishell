#include "../includes/minishell.h"

void	sigintHandler(int signus)
{
    (void)signus;
    printf ("\n Ctrl-C: Deteniendo la ejecución. Volviendo al shell\n");
}

void	sigquitHandler(int signus)
{
    (void)signus;
    printf ("\n Ctrl-\\: Interrumpiendo la ejecución. Volviendo al shell\n");
}

void    init_signals(void)
{
    struct sigaction    sigact;

    sigact.sa_handler = sigintHandler;
    sigemptyset(&sigact.sa_mask);
    sigact.sa_flags = 0;

    if (sigaction(SIGINT, &sigact, NULL) < 0)
    {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }
    sigact.sa_handler = sigquitHandler;
    if (sigaction(SIGQUIT, &sigact, NULL) < 0)
    {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }
    
}