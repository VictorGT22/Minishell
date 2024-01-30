#include "../includes/minishell.h"

char *get_cwd(t_var *var)
{
	char *name = find_in_env(var->env, "USER")->value;
	char cwd[PATH_MAX];	
	char* colored_cwd = malloc(strlen(GREEN) + ft_strlen(name) + strlen(RESET) + strlen(BLUE) + strlen(getcwd(cwd, sizeof(cwd))) + strlen(RESET) + 4);
	strcpy(colored_cwd, GREEN);
	strcat(colored_cwd, name);
	strcat(colored_cwd, RESET);
	strcat(colored_cwd, ":");
	strcat(colored_cwd, BLUE);
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