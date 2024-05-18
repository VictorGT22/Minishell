/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseivane <oseivane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 17:52:00 by oseivane          #+#    #+#             */
/*   Updated: 2024/05/18 17:52:47 by oseivane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	hyphen_case(t_var *var, char *path, char *old_path)
{
	t_env	*oldpwd;
	char	cwd[PATH_MAX];

	oldpwd = find_in_env(var->env, "OLDPWD");
	if (oldpwd)
	{
		printf("%s\n", oldpwd->value);
		path = strdup(oldpwd->value);
	}
	else
		path = getcwd(cwd, sizeof(cwd));
	old_path = getcwd(cwd, sizeof(cwd));
}

void	etc_case(char *path, char *old_path)
{
	int		i;
	char	cwd[PATH_MAX];

	i = 0;
	path = getcwd(cwd, sizeof(cwd));
	old_path = strdup(path);
	i = ft_strlen(path) - 1;
	while (path[i] && path[i] != '/')
	{
		path[i] = '\0';
		i--;
	}
}

void	slash_case(char *path, char *old_path, char **params)
{
	char	cwd[PATH_MAX];

	old_path = getcwd(cwd, sizeof(cwd));
	path = ft_strcat(ft_strcat(getcwd(cwd, sizeof(cwd)),
				"/"), params[1]);
}

void	other_case(char *path, char *old_path, char **params)
{
	char	cwd[PATH_MAX];

	old_path = getcwd(cwd, sizeof(cwd));
	path = params[1];
}


void	ft_cd(t_var *var, char **params)
{
	char	cwd[PATH_MAX];
	char	*path;
	char	*old_path;

	if (params[1])
	{
		if (ft_strcmp(params[1], "-") == 0)
			hyphen_case(var, path, old_path);
		else if (ft_strcmp(params[1], "..") == 0)
			etc_case(path, old_path);
		else if (params[1][0] != '/')
			slash_case(path, old_path, *params);
		else
			other_case(path, old_path, *params);
		change_path(var, params[1], path, old_path);
	}
	else
	{
		old_path = getcwd(cwd, sizeof(cwd));
		path = "/";
		change_path(var, params[1], path, old_path);
	}
}
