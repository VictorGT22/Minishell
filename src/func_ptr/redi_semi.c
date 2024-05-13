/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_ptr4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseivane <oseivane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:29:59 by oseivane          #+#    #+#             */
/*   Updated: 2024/05/13 11:22:11 by oseivane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_redirection_out(t_var *var, t_info_tree *tree)
{
	int	fd;

	if (tree->left->command)
	{
		fd = open(tree->right->command, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		dup2(fd, 1);
		func_pipe(var, tree->left->command);
		close(fd);
	}
}

void	ft_doubleredirection_out(t_var *var, t_info_tree *tree)
{
	int	fd;

	if (tree->left->command)
	{
		fd = open(tree->right->command,
				O_WRONLY | O_APPEND | O_CREAT | O_TRUNC, 0777);
		dup2(fd, 1);
		func_pipe(var, tree->left->command);
		close(fd);
	}
}

void	ft_redirection_in(t_var *var, t_info_tree *tree)
{
	int	fd;

	if (tree->left->command)
	{
		fd = open(tree->right->command,
				O_WRONLY | O_APPEND | O_CREAT | O_TRUNC, 0777);
		dup2(fd, 0);
		func_pipe(var, tree->left->command);
		close(fd);
	}
}

void	ft_doubleredirection_in(t_var *var, t_info_tree *tree)
{
	int		fd;
	char	*line;
	char	*str;
	char	**params;

	str = ft_strtrim(tree->right->command, " \t");
	params = malloc(sizeof(char *) * 3);
	params[0] = save_command(str);
	params[1] = save_params(str);
	params[2] = NULL;
	if (params[0][0] != '\0')
	{
		while (1)
		{
			line = readline("> ");
			if (ft_strcmp(line, params[0]) == 0)
				break ;
		}
		if (tree->left->command)
			func_pipe(var, tree->left->command);
		if (params[1])
			func_pipe(var, params[1]);
	}
}

void	ft_semicolon(t_var *var, t_info_tree *tree)
{
	func_pipe(var, tree->left->command);
	if (tree->right)
		func_pipe(var, tree->right->command);
}
