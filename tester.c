#include <stdio.h>
#include <stdlib.h>

int	main()
{
	int resultado = system("./minishell");
	printf("ls -la\n");
    // Verificar si la ejecución fue exitosa
    if (resultado == 0) {
        printf("El archivo se ejecutó correctamente.\n");
    } else {
        printf("Error al ejecutar el archivo.\n");
    }
}