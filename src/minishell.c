/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vics <vics@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 17:52:30 by vics              #+#    #+#             */
/*   Updated: 2024/01/17 12:45:24 by vics             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <limits.h>
#include <linux/limits.h>

char *get_cwd()
{
	char cwd[PATH_MAX];	
	char* colored_cwd = malloc(strlen(BLUE) + strlen(getcwd(cwd, sizeof(cwd))) + strlen(RESET) + 3);
	strcpy(colored_cwd, BLUE);
	strcat(colored_cwd, getcwd(cwd, sizeof(cwd)));
	strcat(colored_cwd, RESET);
	strcat(colored_cwd, "$");
	strcat(colored_cwd, " ");
	return (colored_cwd);
}

void	manage_history(char *line, char **previous_str)
{
	if ((!*previous_str && line ) || (*previous_str && line && ft_strcmp(*previous_str, line) != 0))
		add_history(line);
	if (*previous_str)
		free(*previous_str);
	if (line)
		*previous_str = ft_strdup(line);
}

int main() {
    char *line;
	char *line_cleaned;
	char *previous_str;
	//char cwd[PATH_MAX];

	previous_str = NULL;
	while(1)
	{
		line = readline(get_cwd());
		line_cleaned = ft_strtrim(line, " \t\n");
		manage_history(line_cleaned, &previous_str);
		free(line);
	}
	clear_history();
    return 0;
}