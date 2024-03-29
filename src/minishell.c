/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <mac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 17:52:30 by vics              #+#    #+#             */
/*   Updated: 2024/02/29 10:13:58 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	init_loop(char **argv, char **env)
{
    (void)argv;
	char *line = NULL;
	char *line_cleaned;
	char *previous_str;
    char *path;
    t_var *var = init_struct(env);
    previous_str = NULL;
   
	 while(1)
	{
        path = get_cwd(var);
		line = readline(path);
        line_cleaned = NULL;
        init_signals(READ);
        free(path);
        if (line && line[0] != '\0')
        {
		    line_cleaned = ft_strtrim(line, " \t\n");
		    manage_history(line_cleaned, &previous_str);
        }
		make_binnary_tree(var, line_cleaned);
        signal(SIGINT, SIG_IGN);
		free(line);
	}
    if (previous_str)
        free(previous_str);
	rl_clear_history();
    func_exit(var);
    return 0;
}

int main(int argc, char **argv, char **env) 
{
    int	status;
	(void)argv;
	
	status = 0;
	if (argc == 1)
	{
		init_loop(argv, env);
	}
	return (status);
}