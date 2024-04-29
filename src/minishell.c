#include "../includes/minishell.h"

int	init_loop(char **argv, char **env)
{
	char	*line;
	char	*line_cleaned;
	char	*previous_str;
	char	*path;
	t_var	*var;

	(void)argv;
	line = NULL;
	var = init_struct(env);
	previous_str = NULL;
	while (1)
	{
		init_signals(READ);
		path = get_cwd(var);
		line = readline(path);
		line_cleaned = NULL;
		update_signal(var->env);
		free(path);
		if (line && line[0] != '\0')
		{
			line_cleaned = ft_strtrim(line, " \t\n");
			manage_history(line_cleaned, &previous_str);
		}
		update_signal(var->env);
		make_binnary_tree(var, line_cleaned);
		ft_printall(var);
		//toString_t_var(var);
		free(line);
	}
	if (previous_str)
		free(previous_str);
	rl_clear_history();
	func_exit(var);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	(void)argv;
	printf("esto esta funcionando?????\n");
	g_exit_sig = 0;
	if (argc == 1)
	{
		init_loop(argv, env);
	}
	else if (argc != 1 || argv[1] != NULL)
	{
		printf("Error: too many arguments\n");
		exit(1);
	}
	printf("salee\n");
	return (EXIT_SUCCESS);

}
