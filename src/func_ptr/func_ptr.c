#include "../../includes/minishell.h"

void	ft_pwd(t_var *var, char **params)
{
	(void)params;
	(void)var;
	char cwd[PATH_MAX];

	printf("%s\n", getcwd(cwd, sizeof(cwd)));
}

void	update_oldpwd(t_var *var, char *newpwd)
{
	t_env *oldpwd;
	char cwd[PATH_MAX];
	(void)cwd;
	oldpwd = find_in_env(var->env, "OLDPWD");
	if (oldpwd)
	{
		free(oldpwd->value);
		oldpwd->value = strdup(newpwd);
	}
	else
		add_in_env(var, strdup("OLDPWD"), strdup(newpwd));
}

void	change_path(t_var *var, char *param, char *path, char *old_path)
{
	if (chdir(path) == -1)
	{
		printf("ENTRAAAA\n");
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
	params[1] = ft_newold(ft_strtrim(params[1], " \t"), params[1]);
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
			path = ft_strtrim(params[1], " \t");
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

