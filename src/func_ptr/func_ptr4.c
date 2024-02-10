#include "../../includes/minishell.h"

void	ft_echo(t_var *var, char **params)
{
	int index_dash;
	int index_end;
	char *flag = NULL;
	char *temp;
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
			temp = ft_substr(params[1], index_end, ft_strlen(params[1]));
			str = ft_strtrim(temp ," \t");
			printf("%s", str);
			free(str);
			free(temp);
		}
		else
			printf("%s", params[1]);
	}
	if (!params[1] || index_dash == -1 || ft_strcmp(flag, "-n") != 0)
		printf("\n");
	if (flag)
		free(flag);
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

