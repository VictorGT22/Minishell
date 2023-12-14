/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vics <vics@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 17:52:30 by vics              #+#    #+#             */
/*   Updated: 2023/12/13 15:55:40 by vics             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <limits.h>
#include <linux/limits.h>

int main() {
    char *line;
	char *previous_str;
	char cwd[PATH_MAX];

	previous_str = NULL;
	while(1)
	{
		if (getcwd(cwd, sizeof(cwd)) != NULL)
		{
			blue();
       		printf("%s ", cwd);
			resetColor();
		}
		line = readline("$ ");
		if ((!previous_str && line ) || (previous_str && line && ft_strcmp(previous_str, line) != 0))
		{
			add_history(line);
			printf("Diferente a la anterior\n");
		}
		if (previous_str)
			free(previous_str);
		if (line)
			previous_str = ft_strdup(line);
		printf("%s", previous_str);
		printf("La línea ingresada es: %s\n", line);
		free(line);
		
	}

   
	
    return 0;
}