#include "../includes/minishell.h"

char *get_cwd(t_var *var)
{
	int len;
	char *path;
	t_env *env_user;
	char cwd[PATH_MAX];
	char* colored_cwd;

	
	path = getcwd(cwd, sizeof(cwd));
	env_user = find_in_env(var->env, "USER");
	if (path)
	{
		len = ft_strlen(GREEN) + ft_strlen(env_user->value) + ft_strlen(RESET) + ft_strlen(BLUE) + ft_strlen(path) + ft_strlen(RESET) + 4;
		colored_cwd = malloc(sizeof(char) * len + 1);
		ft_bzero(colored_cwd, len + 1);
		if (env_user)
		{
			colored_cwd = ft_newold(ft_strcat(colored_cwd, GREEN), colored_cwd);
			colored_cwd = ft_newold(ft_strcat(colored_cwd, env_user->value), colored_cwd);
			colored_cwd = ft_newold(ft_strcat(colored_cwd, RESET), colored_cwd);
			colored_cwd = ft_newold(ft_strcat(colored_cwd, ":"), colored_cwd);
		}
		colored_cwd = ft_newold(ft_strcat(colored_cwd, BLUE), colored_cwd);
		colored_cwd = ft_newold(ft_strcat(colored_cwd, path), colored_cwd);
		colored_cwd = ft_newold(ft_strcat(colored_cwd, RESET), colored_cwd);
		colored_cwd = ft_newold(ft_strcat(colored_cwd, "$"), colored_cwd);
		colored_cwd = ft_newold(ft_strcat(colored_cwd, " "), colored_cwd);
	}
	else
		colored_cwd = ft_strdup("$ ");
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