#include "../../includes/minishell.h"

void	ft_exit(t_var *var, char **params)
{
	//HACER TODOS LOS FREES
	printf("exit\n");
	func_exit(var);
	exit(0); //cambiar 0 por exit code
}

char *ft_strcat(char *dest, char *src)
{
    char *temp; 
    int i = 0;
    int n = 0;

    temp = malloc(sizeof(char) * (ft_strlen(dest) + ft_strlen(src)) + 2);
    if (!temp)
        return (NULL);
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

char *ft_newold(char *new, char *old)
{
	free(old);
	return (new);
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
        temp = ft_newold(ft_strcat(paths[i], "/"), temp);
        temp = ft_newold(ft_strcat(temp, function), temp);
        fd = access(temp, F_OK);
        if (fd != -1)
            return (temp);
		free(temp);
        i++;
    }
    return (ft_strdup("-1"));
}

void	execute_action(t_var *var, char **params)
{
	char **path = ft_split(find_in_env(var->env, "PATH")->value, ':');
	char *execution_path = find_func(path, params[0]);
    pid_t pid = fork();

    
    if (pid == -1)
        return;
    else if (pid == 0)
	{
        printf("entra: %s\n", execution_path);
        if (execve(execution_path, params, NULL) < 0)
		{
            printf("no puedo ejec");
			if (access(params[0], F_OK) != -1 && params[0][0] != '\0')
			{
                printf("y aquinentra???");
				if (execve(params[0], params, NULL) < 0)
					exec_error(params[0], NO_PERM);
			}
			else
				exec_error(params[0], NOT_FOUND);			
		}
        exit(0);
    } else {
        wait(NULL);
		free_arr(path);
		free(execution_path);
        return;
    }
	
}