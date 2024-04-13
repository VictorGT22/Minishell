#include "../../includes/minishell.h"

void	ft_echo(t_var *var, char **params)
{
	int i = 0;
	char **arr = NULL;
	bool flag = false;

	if (params[1])
	{
		arr = ft_split(params[1], ' ');
		if (strcmp(arr[0], "-n") == 0)
		{
			flag = true;
			i = 1;
		}
		while (arr[i])
		{
			printf("%s", arr[i]);
			i++;
			if (arr[i])
				printf(" ");
		}
	}
	if (!flag || !params[1])
		printf("\n");
}

void	ft_redirection_out(t_var *var, t_info_tree *tree)
{
	int fd;

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
	int fd;

	if (tree->left->command)
	{
		fd = open(tree->right->command, O_WRONLY | O_APPEND| O_CREAT | O_TRUNC, 0777);
		dup2(fd, 1);
		func_pipe(var, tree->left->command);
		close(fd);	
	}
}

void	ft_redirection_in(t_var *var, t_info_tree *tree)
{
	int fd;

	if (tree->left->command)
	{
		fd = open(tree->right->command, O_WRONLY | O_APPEND| O_CREAT | O_TRUNC, 0777);
		dup2(fd, 0);
		func_pipe(var, tree->left->command);
		close(fd);	
	}
}

void	ft_doubleredirection_in(t_var *var, t_info_tree *tree)
{
	int fd;
	char *line;
	char *str = ft_strtrim(tree->right->command, " \t");
    char **params = malloc(sizeof(char *) * 3);
    params[0] = save_command(str);
    params[1] = save_params(str);
    params[2] = NULL;
	if (params[0][0] != '\0')
	{
		while (1)
		{
			line = readline("> ");
			if (ft_strcmp(line, params[0]) == 0)
				break;
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

