#include "../includes/minishell.h"

void    funcion_prueba(t_var *var, char *params)
{
    
}

void	ft_cd(t_var *var, char *params)
{
	char cwd[PATH_MAX];

	if (params[1])
	{
		if (ft_strcmp(params[1], "-") == 0 && find_in_env(var->env, "OLDPWD"))
		{
			add_in_env(var, "OLDPWD", getcwd(cwd, sizeof(cwd)));
			chdir(find_in_env(var->env, "OLDPWD")->value);

		}

	}

}

char *ft_strcat(char *dest, char *src)
{
    char *temp = malloc(sizeof(char) * (ft_strlen(dest) + ft_strlen(src)) + 2);
    int i = 0;
    int n = 0;

    ft_memset(temp, '\0', (ft_strlen(dest) + ft_strlen(src)) + 2);
    while (dest[i] != '\0') {
        temp[i] = dest[i];
        i++;
    }
    while (src[n] != '\0') {
        temp[i] = src[n];
        i++;
        n++;
    }
    temp[i] = '\0';
    return (temp);
}

char *find_func(char **paths, char *function)
{
    char *temp = NULL;
    int i = 0;
    int fd = -1;

    while (paths[i] != NULL) {
        temp = malloc(sizeof(char) * (ft_strlen(paths[i])
        + ft_strlen(function)) + 2);
        ft_memset(temp, '\0', (ft_strlen(paths[i]) + ft_strlen(function)) + 2);
        temp = ft_strcat(paths[i], "/");
        temp = ft_strcat(temp, function);
        fd = access(temp, F_OK);
        if (fd != -1)
		{
			printf("#%s#\n", temp);
            return (temp);
		}
		free(temp);
        i++;
    }
    return ("-1");
}

void	execute_action(t_var *var, char **params)
{
	char **path = ft_split(find_in_env(var->env, "PATH")->value, ':');
	char *execution_path = find_func(path, params[0]);
    pid_t pid = fork();
    char **exec_params = malloc(sizeof(char *));

    exec_params[0] = ft_strcat("./", params[0]);
    exec_params[1] = NULL;
    exec_params[2] = NULL;
    if (pid == -1) {
        return;
    } else if (pid == 0) {
		if (ft_strcmp(execution_path, "-1") == 0)
			exec_error(params[0], NOT_FOUND);
        else if (execve(execution_path, exec_params, NULL) < 0)
            printf("\nCould not execute command..");
        exit(0);
    } else {
        wait(NULL);
        return;
    }
}

void    save_actions(t_var *var)
{
    var->act = malloc(sizeof(t_actions) * NUM_ACTIONS + 1);
    var->act[0].action = EXIT;
	var->act[0].function = &funcion_prueba;
	var->act[1].action = ECHO;
	var->act[1].function = &funcion_prueba;
	var->act[2].action = PWD;
	var->act[2].function = &funcion_prueba;
	var->act[3].action = CD;
	var->act[3].function = &funcion_prueba;
	var->act[4].action = EXPORT;
	var->act[4].function = &funcion_prueba;
	var->act[5].action = UNSET;
	var->act[5].function = &funcion_prueba;
	var->act[6].action = ENV;
	var->act[6].function = &funcion_prueba;
	var->act[7].action = HELP;
	var->act[7].function = &funcion_prueba;
    var->act[8].action = NULL;	
}

void    function_ptr(t_var *var, char **params)
{
    int i = 0;

    while (var->act[i].action)
    {
		if (ft_strcmp(params[0], var->act[i].action) == 0)
		{
			printf("entra\n");
			break;
		}
        i++;
    }
	if (!var->act[i].action)
		execute_action(var, params);
}