/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <mac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 17:52:30 by vics              #+#    #+#             */
/*   Updated: 2024/02/22 11:13:53 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(int argc, char **argv, char **env) {
    char *line = NULL;
	char *line_cleaned;
	char *previous_str;
    char *path;
    (void)argc;
    (void)argv;
    t_var *var = init_struct(env);
    previous_str = NULL;
   
	 while(1)
	{
        path = get_cwd(var);
		line = readline(path);
        line_cleaned = NULL;
        free(path);
        init_signals();
        if (line && line[0] != '\0')
        {
		    line_cleaned = ft_strtrim(line, " \t\n");
		    manage_history(line_cleaned, &previous_str);
        }
		make_binnary_tree(var, line_cleaned);
		free(line);
	}
    if (previous_str)
        free(previous_str);
	rl_clear_history();
    func_exit(var);
    return 0;
}