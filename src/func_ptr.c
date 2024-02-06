#include "../includes/minishell.h"

void    funcion_prueba(t_var *var, char **params)
{
    
}

void	ft_pwd(t_var *var, char **params)
{
	char cwd[PATH_MAX];

	printf("%s\n", getcwd(cwd, sizeof(cwd)));
}

void	update_oldpwd(t_var *var, char *newpwd)
{
	t_env *oldpwd;
	char cwd[PATH_MAX];

	oldpwd = find_in_env(var->env, "OLDPWD");
	if (oldpwd)
	{
		free(oldpwd->value);
		oldpwd->value = strdup(newpwd);
	}
	else
		add_in_env(var, strdup("OLDPWD"), strdup(newpwd));
}

void	change_path(t_var *var, char*param, char *path, char *old_path)
{
	if (chdir(path) == -1)
	{
		if (access(path, R_OK) == 0)
			exec_error(param, NO_DIR);
		else
			exec_error(param, NO_EXIST);
	}
	else
		update_oldpwd(var, old_path);
}

void	ft_cd(t_var *var, char **params)
{
	char cwd[PATH_MAX];
	t_env *oldpwd;
	char *path;
	char *old_path;
	int i = 0;

	oldpwd = find_in_env(var->env, "OLDPWD");
	if (params[1])
	{
		if (ft_strcmp(params[1], "-") == 0)
		{
			if (oldpwd)
			{
				printf("%s\n", oldpwd->value);//print del path
				path = strdup(oldpwd->value);
			}
			else
				path = getcwd(cwd, sizeof(cwd));
			old_path = getcwd(cwd, sizeof(cwd));
		}
		else if (ft_strcmp(params[1], "..") == 0)
		{
			path = getcwd(cwd, sizeof(cwd));
			old_path = strdup(path);
			i = ft_strlen(path) - 1;
			while (path[i] && path[i] != '/')
			{
				path[i] = '\0';
				i--;
			}
		}
		else if (params[1][0] != '/')
		{
			old_path = getcwd(cwd, sizeof(cwd));
			path = ft_strcat(ft_strcat(getcwd(cwd, sizeof(cwd)), "/"), params[1]);
		}
		else
		{
			old_path = getcwd(cwd, sizeof(cwd));
			path = params[1];
		}
		change_path(var, params[1], path, old_path);
	}
	else
	{
		old_path = getcwd(cwd, sizeof(cwd));
		path = "/";
		change_path(var, params[1], path, old_path);
	}

}

void	print_env(t_var *var, char *str)
{
	t_env *tmp = var->env;
	while (tmp)
	{
		printf("%s %s:%s\n", str, tmp->name, tmp->value);
		tmp = tmp->next;
	}
}

void	ft_unset(t_var *var, char**params)
{
	t_env *env_name;
	char *name;
	int index;

	if (params[1])
	{
		index = ft_strchr_index(params[1], '=');
		name = name = ft_substr(params[1], 0, index);
		env_name = find_in_env(var->env, name);
		if (env_name)
			ft_lstdelone_env(&var->env, env_name);
	}
}

void	get_add_var_env(t_var *var, char **params, int index)
{
	char *name;
	char *value;
	t_env *env_name;

	name = ft_substr(params[1], 0, index);
	value = ft_substr(params[1], index + 1, ft_strlen(params[1]) - index + 1);
	env_name = find_in_env(var->env, name);
	if (!env_name)
		add_in_env(var, ft_strdup(name), ft_strdup(value));
	else
	{
		free(env_name->value);
		env_name->value = ft_strdup(value);
	}
	if (ft_strcmp(params[0], "env") == 0)
		print_env(var, "");
}

void	ft_export(t_var *var, char **params)
{
	if (params[1] && ft_strchr_index(params[1], '=') != -1)
		get_add_var_env(var, params, ft_strchr_index(params[1], '='));
	else
		print_env(var, "declare -x");
}

void	ft_env(t_var *var, char **params)
{
	int index;

	if (ft_strcmp(params[0], "env") == 0)
	{
		
		if (!params[1] || params[1][0] == '\0')
			print_env(var, "");
		else if (params[1] && ft_strchr_index(params[1], '=') != -1)
			get_add_var_env(var, params, ft_strchr_index(params[1], '='));
	}
}

void	ft_help(t_var *var, char **params)
{
	
	printf("\033[0;35m\tHOW TO USE MINISHELL:\n\033[0m");
	printf("Bash is a command-line interpreter and scripting language.\n\n");
	printf("Commands:\t\tActions:\n______________________________\n");
	printf("\033[0;33mecho:\033[0m (flag -n) Display text or output to the terminal\n");
	printf("\033[0;33mpwd:\033[0m Print working directory\n");
	printf("\033[0;33mexport:\033[0m Used to set an environment variable\n");
	printf("\033[0;33munset:\033[0m Used to unset or delete a variable or function\n");
	printf("\033[0;33menv:\033[0m Used to display or modify the environment variables\n\n");

}

void	ft_echo(t_var *var, char **params)
{
	int index_dash;
	int index_end;
	char *flag = "";
	char *str = "";

	if (params[1])
	{
		index_dash = ft_strchr_index(params[1], '-');
		index_end = ft_strchr_index(params[1], ' ');
		if (index_end == -1)
			index_end = ft_strlen(params[1]);
		if (index_dash != -1)
		{
			flag = ft_substr(params[1], index_dash, index_end);
			str = ft_strtrim(ft_substr(params[1], index_end, ft_strlen(params[1])), " \t");
			printf("%s", str);
			free(str);
		}
		else
			printf("%s", params[1]);
		if (index_dash != -1 && ft_strcmp(flag, "-n"))
			free(flag);
		else
			printf("\n");	
	}
	else
		printf("\n");
}

void	ft_exit(t_var *var, char **params)
{
	//HACER TODOS LOS FREES
	printf("exit\n");
	exit(0); //cambiar 0 por exit code
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
            return (temp);
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

    if (pid == -1)
        return;
    else if (pid == 0)
	{
        if (execve(execution_path, params, NULL) < 0)
		{
			if (access(params[0], F_OK) != -1 && params[0][0] != '\0')
			{
				if (execve(params[0], params, NULL) < 0)
					exec_error(params[0], NO_PERM);
			}
			else
				exec_error(params[0], NOT_FOUND);			
		}
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
	var->act[0].function = &ft_exit;
	var->act[1].action = ECHO;
	var->act[1].function = &ft_echo;
	var->act[2].action = PWD;
	var->act[2].function = &ft_pwd;
	var->act[3].action = CD;
	var->act[3].function = &ft_cd;
	var->act[4].action = EXPORT;
	var->act[4].function = &ft_export;
	var->act[5].action = UNSET;
	var->act[5].function = &ft_unset;
	var->act[6].action = ENV;
	var->act[6].function = &ft_env;
	var->act[7].action = HELP;
	var->act[7].function = &ft_help;
    var->act[8].action = NULL;	
}

void    function_ptr(t_var *var, char **params)
{
    int i = 0;
    while (var->act[i].action)
    {
		if (ft_strcmp(params[0], var->act[i].action) == 0)
		{
			 (*(var->act[i].function))(var, params);
			break;
		}
        i++;
    }
	if (!var->act[i].action)
		execute_action(var, params);
}