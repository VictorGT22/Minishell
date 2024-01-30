//Manejar las señales Ctrl-c, Ctrl-D y Ctrl-/
#include "../includes/minishell.h"

void	sigintHandler(int signus)
{
    printf ("\n Ctrl-C: Deteniendo la ejecución. Volviendo al shell\n");
    exit(EXIT_SUCCESS);
}

void	sigquitHandler(int signus)
{
    printf ("\n Ctrl-\\: Interrumpiendo la ejecución. Volviendo al shell\n");
    exit(EXIT_SUCCESS);
}