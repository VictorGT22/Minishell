/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseivane <oseivane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:34:10 by oseivane          #+#    #+#             */
/*   Updated: 2024/05/18 17:52:36 by oseivane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_pwd(t_var *var, char **params)
{
	char	cwd[PATH_MAX];

	(void)params;
	(void)var;
	printf("%s\n", getcwd(cwd, sizeof(cwd)));
}

void	update_oldpwd(t_var *var, char *newpwd)
{
	t_env	*oldpwd;
	char	cwd[PATH_MAX];

	(void)cwd;
	oldpwd = find_in_env(var->env, "OLDPWD");
	if (oldpwd)
	{
		free(oldpwd->value);
		oldpwd->value = ft_strdup(newpwd);
	}
	else
		add_in_env(var, ft_strdup("OLDPWD"), ft_strdup(newpwd));
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
