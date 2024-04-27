#ifndef DEFINITIONS_H
# define DEFINITIONS_H

//COLORS
#define BLUE "\033[0;34m"
#define GREEN "\033[0;32m"
#define RESET "\033[0m"

//SIGNAL
int	g_exit_sig;

# define READ		1
# define HEREDOC	2
# define EXEC		3

//ACTIONS
#define NUM_ACTIONS 9
#define EXIT "exit"
#define ECHO "echo"
#define PWD "pwd"
#define CD "cd"
#define EXPORT "export"
#define UNSET "unset"
#define ENV "env"
#define HELP "help"

//ERROR MSG
#define WRONG_OP_NL "minishell: syntax error near unexpected token 'new line'\n"
#define WRONG_OP "minishell: syntax error near unexpected token"
#define NO_CLOSED "minishell: syntax error no closed quote\n"
#define NOT_FOUND "command not found\n"
#define NO_PERM "Permission denied\n"
#define NO_DIR "Not a directory\n"
#define NO_EXIST "No such file or directory.\n"
#define NO_FORK "Error. Fork no created\n"

#endif

#ifndef MINISHELL_H
# define MINISHELL_H

//System .h files
# include <unistd.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/signal.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <limits.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <sys/wait.h>

// Radline .h files
# include "../readline/readline.h"
# include "../readline/history.h"

// Our .h files
# include "../libft/libft.h"
# include "structs.h"
# include "definitions.h"

//INITIALIZE
int	init_loop(char **argv, char **env);
t_var *init_struct(char **env);
t_info_tree *init_linked_tree(char *command, char *operator, char *prev_op);
t_info_tree *init_struct_tree(void);

//ENVIROMENT
void 	save_env(t_var *var, char **env);
t_env 	*find_in_env(t_env *lst, char *name);
void	add_in_env(t_var *var, char *name, char *value);
void 	ft_lstdelone_env(t_env **lst, t_env *todelate);

//INPUT
char 	*get_cwd(t_var *var);
void	manage_history(char *line, char **previous_str);

//UTILS
int		valid_chars(char n);
char	*ft_strcat(char *dest, char *src);
void    func_exit(t_var *var);
char 	*ft_newold(char *new, char *old);

//TREE OPERATIONS
bool	ft_replace_chrchr(char *str, char find, char replace);
char 	*ft_replace_strstr(char *string, int index, int len, char *replace);
void	ft_remove_chr(char *str, char find);
char *save_sentence_r(char *string, int num);
char *save_sentence_l(char *string, int num);
void    check_operator(t_info_tree *tree);

//FREE
void	free_arr(char **arr);
void 	free_binnarytree(t_info_tree *tree);
void 	make_binnary_tree(t_var *var, char *line);

//GET INFORMATION
int 	get_biggest_priority(char *string);
char	*get_operator(char *string, int j);
char	*save_params(char *str);
char	*save_command(char *str);

//SIGNALS
void		update_signal(t_env *env);
static void	read_handler(int signal, siginfo_t *data, void *n_data);
static void	heredoc_handler(int signal, siginfo_t *data, void *n_data);
static void	exec_handler(int signal, siginfo_t *data, void *n_data);
void		init_signals(int mode);

//FUNCTION PTR
void    save_actions(t_var *var);
void    function_ptr(t_var *var, char **params);

void    save_actions_op(t_var *var);
void    function_ptr_op(t_var *var, t_info_tree *tree);

void	ft_echo(t_var *var, char **params);
void	ft_pwd(t_var *var, char **params);
void	update_oldpwd(t_var *var, char *newpwd);
void	change_path(t_var *var, char*param, char *path, char *old_path);
void	ft_cd(t_var *var, char **params);
void	print_env(t_var *var, char *str);
void	ft_exit(t_var *var, char **params);
char	*ft_strcat(char *dest, char *src);
char	*find_func(char **paths, char *function);
void	execute_action(t_var *var, char **params);
void	ft_unset(t_var *var, char**params);
void	ft_help(t_var *var, char **params);
void	get_add_var_env(t_var *var, char **params, int index);
void	ft_export(t_var *var, char **params);
void	ft_env(t_var *var, char **params);
void	ft_redirection_out(t_var *var, t_info_tree *tree);
void	ft_doubleredirection_out(t_var *var, t_info_tree *tree);
void	ft_redirection_in(t_var *var, t_info_tree *tree);
void	ft_doubleredirection_in(t_var *var, t_info_tree *tree);
void	ft_semicolon(t_var *var, t_info_tree *tree);

//ERROR
void    stx_error(char *error_msg);
void    exec_error(char *command, char *error_msg);
void    stx_error_op(char *error_msg, char op);

//PIPES
int		func_pipe(t_var *var, char *command);

#endif

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_var t_var;

typedef struct s_info_tree {
	char *operator;
	char *prev_operator;
	char *command;
	int checked;
	struct s_info_tree *left;
	struct s_info_tree *right;
} t_info_tree;

typedef struct s_env {
	char *name;
	char *value;
	int 	end_type;
	struct s_env *prev;
	struct s_env *next;
} t_env;

typedef struct s_actions {
	char *action;
	void (*function)(t_var *var, char **params);
} t_actions;

typedef struct s_actions_op {
	char *action;
	void (*function)(t_var *var, t_info_tree *tree);
} t_actions_op;

typedef struct s_var {
	struct s_info_tree *tree;
	struct s_env *env;
	struct s_actions *act;
	struct s_actions_op *op;
} t_var;

typedef struct s_pipe {
	int **pipes;
	int save;
	int num_pipes;
} t_pipe;

#endif

#include "../includes/minishell.h"

int valid_chars(char n)
{
    if (n == '\0' || n == '\n'
    || n == '<' || n == ';' || n == '>'
    || n == '(' || n == ')' || n == '&')
        return 1;
    return 0;
}

int return_priority(char operator)
{
    if (operator == ')')
        return 3;
    if (operator == ';')
        return 2;
    if (operator == '<' || operator == '>' || operator == '&')
        return 1;
    return (-1);
}

int len_operator(char *str, int i)
{
    char c = str[i];
    int len = 0;
    while(str[i] && str[i] == c)
    {
        i++;
        len++;
    }
    return (len);
}

char *get_operator(char *string, int j)
{
    int i = 0;
    int len = len_operator(string, j);
    char *operator = malloc(sizeof(char) * len + 1);

    while (valid_chars(string[j])) {
        operator[i] = string[j];
        i++;
        j++;
    }
    operator[i] = '\0';
    return (operator);
}

int get_biggest_priority(char *string)
{
    int i = 0;
    char c = '\0';
    int pos = -1;
    int biggest = -1;

    if (string == NULL)
        return (-1);
    while (string[i] != '\0') {
        if (string[i] == '"' || string[i] == '\'')
        {
            if (c)
                c = '\0';
            else
                c = string[i];
        }
        if (return_priority(string[i]) > biggest && !c) {
            biggest = return_priority(string[i]);
            pos = i;
        }
        i++;
    }
	return (pos);
}


char *save_command(char *str)
{
    int i = 0;
    char *command;

    while (str[i] && str[i] != ' ')
        i++;
    command = malloc(sizeof(char) * i + 1);
    i = 0;
    while (str[i] && str[i] != ' ')
    {
        command[i] = str[i];
        i++;
    }
    command[i] = '\0';
    return (command);
}

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

#include "../../includes/minishell.h"

void	ft_unset(t_var *var, char**params)
{
	t_env *env_name;
	char *name;
	int index;

	if (params[1])
	{
		index = ft_strchr_index(params[1], '=');
		name = ft_substr(params[1], 0, index);
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
	if (isalpha(name[0]))
	{
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
	else
		printf("minishell: %s: '%s': not a valis identifier\n", params[0], params[1]);
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
		free_arr(path);
		free(execution_path);
        return;
    }
	
}

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

#include "../../includes/minishell.h"

void    save_actions_op(t_var *var)
{
    var->op = malloc(sizeof(t_actions_op) * NUM_ACTIONS + 1);
    var->op[0].action = ">";
	var->op[0].function = &ft_redirection_out;
	var->op[1].action = ">>";
	var->op[1].function = &ft_doubleredirection_out;
	var->op[2].action = "<";
	var->op[2].function = &ft_redirection_in;
	var->op[3].action = "<<";
	var->op[3].function = &ft_doubleredirection_in;
	var->op[4].action = ";";
	var->op[4].function = &ft_semicolon;
    var->op[5].action = NULL;	
}

void    function_ptr_op(t_var *var, t_info_tree *tree)
{
    int i = 0;
    while (var->op[i].action)
    {
		if (ft_strcmp(tree->operator, var->op[i].action) == 0)
		{
			 (*(var->op[i].function))(var, tree);
			break;
		}
        i++;
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

char *save_params(char *str)
{
    int i = 0;
    int j = 0;
    char *param;

    while (str[i] && str[i] != ' ')
        i++;
    if (str[i] == ' ')
        i++;
    j = ft_strlen(&str[i]);
    param = malloc(sizeof(char) * j + 1);
    j = 0;
    while (str[i])
    {
        param[j] = str[i];
        i++;
        j++;
    }
    param[j] = '\0';
    if (!param[0])
        return (NULL);
    return (param);
}

#include "../includes/minishell.h"

t_var *init_struct(char **env)
{
    t_var *var = malloc(sizeof(t_var));
    save_env(var, env);
    save_actions(var);
    save_actions_op(var);
    return (var);
}

t_info_tree *init_linked_tree(char *command, char *operator, char *prev_op)
{
    (void)prev_op;
    t_info_tree *file = malloc(sizeof(t_info_tree) * 1);

    if (file == NULL)
        perror("error\n");
    file->operator = operator;
    file->command = command;
    //file->prev_operator = NULL;
    //if (prev_op != NULL)
     //   file->prev_operator = strdup(prev_op);
    //file->checked = 0;
    file->right = NULL;
    file->left = NULL;
    return file;
}

t_info_tree *init_struct_tree(void)
{
    t_info_tree *file = malloc(sizeof(t_info_tree) * 1);

    file->operator = NULL;
    file->right = NULL;
    file->left = NULL;
    return file;
}

#include "../includes/minishell.h"

char *get_cwd(t_var *var)
{
	char *name = find_in_env(var->env, "USER")->value;
	char cwd[PATH_MAX];	
	char* colored_cwd = malloc(strlen(GREEN) + ft_strlen(name) + strlen(RESET) + strlen(BLUE) + strlen(getcwd(cwd, sizeof(cwd))) + strlen(RESET) + 4);
	//colored_cwd = "prueba";
	strcpy(colored_cwd, GREEN);
	colored_cwd = ft_newold(ft_strcat(colored_cwd, name), colored_cwd);
	colored_cwd = ft_newold(ft_strcat(colored_cwd, RESET), colored_cwd);
	colored_cwd = ft_newold(ft_strcat(colored_cwd, ":"), colored_cwd);
	colored_cwd = ft_newold(ft_strcat(colored_cwd, BLUE), colored_cwd);
	colored_cwd = ft_newold(ft_strcat(colored_cwd, getcwd(cwd, sizeof(cwd))), colored_cwd);
	colored_cwd = ft_newold(ft_strcat(colored_cwd, RESET), colored_cwd);
	colored_cwd = ft_newold(ft_strcat(colored_cwd, "$"), colored_cwd);
	colored_cwd = ft_newold(ft_strcat(colored_cwd, " "), colored_cwd);
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

#include "../includes/minishell.h"

void init_pipes_func(t_pipe *struct_pipes)
{
    int i = 0;

    struct_pipes->pipes = malloc(sizeof(int *) * struct_pipes->num_pipes);
    for (i = 0; i < struct_pipes->num_pipes; i++)
        struct_pipes->pipes[i] = malloc(sizeof(int) * 2);
    struct_pipes->save = dup(1);
}

void dup_functions(int i, int pipes_nbr, int save, int **pipes)
{
    if (i + 1 < pipes_nbr)
        dup2(pipes[i][1], 1);
    else
        dup2(save, 1);
    if (i != 0) {
        dup2(pipes[i - 1][0], 0);
        close(pipes[i - 1][1]);
    }
}

void pipes_func_ext(t_var *var, int i, t_pipe *struct_pipes, char **commands_arr)
{
    //int wstatus = -1;
    
    char *str = ft_strtrim(commands_arr[i], " \t");
    char **params = malloc(sizeof(char *) * 3);
    params[0] = save_command(str);
    params[1] = save_params(str);
    params[2] = NULL;
    dup_functions(i, struct_pipes->num_pipes, struct_pipes->save, struct_pipes->pipes);
    function_ptr(var, params);
	free(str);
	free_arr(params);
}

int func_pipe(t_var *var, char *command)
{
    char **commands_arr;
    //int num_pipes;
    t_pipe *struct_pipes;
    
    if (!command)
        return (-1);
    commands_arr = ft_split(command, '|');
    if (!commands_arr)
        return (-1);
    struct_pipes = malloc(sizeof(t_pipe));
    if (!struct_pipes)
    {
        free_arr(commands_arr);
        return (-1);
    }
    struct_pipes->num_pipes = ft_arrlen(commands_arr);
    if (struct_pipes->num_pipes <= 0)
    {
        free_arr(commands_arr);
        free(struct_pipes);
        return (-1);
    } 
    init_pipes_func(struct_pipes);
    for(int i = 0; i < struct_pipes->num_pipes; i++)
        if (pipe(struct_pipes->pipes[i]) == -1)
            return (84);
    for (int i = 0; i < struct_pipes->num_pipes; i++)
        pipes_func_ext(var, i, struct_pipes, commands_arr);
	for (int i = 0; i < struct_pipes->num_pipes; i++)
        free(struct_pipes->pipes[i]);
	free_arr(commands_arr);
	free(struct_pipes->pipes);
	free(struct_pipes);
	return (0);   
}

#include "../includes/minishell.h"

void	update_signal(t_env *env)
{
	if (g_exit_sig)
		env->end_type = g_exit_sig;
}

static void	read_handler(int signal, siginfo_t *data, void *n_data)
{
	(void) data;
	(void) n_data;
	if (signal == SIGINT)
	{
		g_exit_sig = 1;
		ft_putstr_fd("\n", STDERR_FILENO);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
    // else if (signal == SIGQUIT)
	// {
	// 	ft_putstr_fd("Quit: 3\n", STDERR_FILENO);
    //     rl_on_new_line();
	// 	rl_replace_line("", 1);
	// }
}

static void	heredoc_handler(int signal, siginfo_t *data, void *n_data)
{
	(void) data;
	(void) n_data;
	if (signal == SIGINT)
	{
		ft_putstr_fd("\n", STDERR_FILENO);
		rl_replace_line("", 1);
		exit(1);
	}
}

static void	exec_handler(int signal, siginfo_t *data, void *n_data)
{
	(void) data;
	(void) n_data;
	if (signal == SIGINT)
	{
		g_exit_sig = 130;
		ft_putstr_fd("\n", STDERR_FILENO);
		rl_replace_line("", 1);
	}
	else if (signal == SIGQUIT)
	{
		g_exit_sig = 131;
		ft_putstr_fd("Quit: 3\n", STDERR_FILENO);
		rl_replace_line("", 1);
	}
}

// void eof_handler(int signal)
// {
//     if (signal == SIGQUIT)
//     {
//         ft_putstr_fd("Exit\n", STDERR_FILENO);
//         exit(EXIT_SUCCESS); // O cualquier otro comportamiento que desees
//     }
// }

void	init_signals(int mode)
{
	struct sigaction	sig;

	sig.sa_flags = SA_RESTART;
	sigemptyset(&sig.sa_mask);
	g_exit_sig = 0;
	if (mode == READ)
	{
		sig.sa_sigaction = read_handler;
		signal(SIGQUIT, SIG_IGN);
		sigaction(SIGINT, &sig, NULL);
	}
	else if (mode == HEREDOC)
	{
		sig.sa_sigaction = heredoc_handler;
		signal(SIGQUIT, SIG_IGN);
		sigaction(SIGINT, &sig, NULL);
	}
	else if (mode == EXEC)
	{
		sig.sa_sigaction = exec_handler;
		sigaction(SIGINT, &sig, NULL);
		sigaction(SIGQUIT, &sig, NULL);
	}
	// else if (mode == EOF_MODE) // Modo para manejar EOF
    // {
    //     signal(SIGQUIT, eof_handler); // Manejador específico para EOF
    // }
}

#include "../includes/minishell.h"

char *expansion(t_var *var, char *command)
{
    int i = 0;
    int len = 0;
    int last = 0;
    char *name = NULL;
    char *value_str = NULL;
    t_env *env;
    
    while (last >= 0)
    {
        i = ft_strchr_index(&command[last], '$');
        if (i != -1)
        {
            i += last + 1;
            while (command[i] && ft_isalnum(command[i]))
            {
                i++;
                len++;
            }
        }
        if (len == 0)
            last = -1;
        else
        {
            name = malloc(sizeof(char) * len + 1);
            ft_strlcpy(name, &command[i - len], len + 1);
            env = find_in_env(var->env, name);
            free(name);
            if (env)
                value_str = ft_strdup(env->value);
            else if (!ft_isalpha(command[ft_strchr_index(&command[last], '$') + 1]))
            {
                int index = ft_strchr_index(&command[last], '$') + 2;
                value_str = ft_substr(command, index, len - 1);
            }
            command = ft_replace_strstr(command, i - len - 1, len, value_str);
            last = i - ft_strlen(value_str);
            free(value_str);
            value_str = "";
        }
        len = 0;
    }
    return(command);
}

void recursive_tree(t_var *var, t_info_tree *tree, char *string)
{
    if (string == NULL || tree == NULL)
        return;
    
    int j = get_biggest_priority(string);

    if (j == -1) {
        tree->left = NULL;
        tree->right = NULL;
        tree->operator = NULL;
        tree->command = string;
        ft_remove_chr(tree->command, '"');
        ft_remove_chr(tree->command, '\'');
    } else {
        tree->command = NULL;
        tree->operator = get_operator(string, j);
        tree->left = init_linked_tree(save_sentence_l(string, j), tree->operator, tree->operator);
        tree->right = init_linked_tree(save_sentence_r(string, j), tree->operator, tree->operator);
        check_operator(tree);
        ft_remove_chr(tree->left->command, '"');
        ft_remove_chr(tree->left->command, '\'');
        ft_remove_chr(tree->right->command, '"');
        ft_remove_chr(tree->right->command, '\'');
        recursive_tree(var, tree->left, tree->left->command);
        recursive_tree(var, tree->right, tree->right->command);
    }
}

void recursive2(t_var *var, t_info_tree *tree)
{
    int copia_0 = dup(0);
    int copia_1 = dup(1);

    if (tree->operator != NULL)
        function_ptr_op(var, tree);
    if (tree->left != NULL && tree->left->left != NULL)
        recursive2(var, tree->left);
    if (tree->operator == NULL)
        func_pipe(var, tree->command);
    if (tree->right != NULL && tree->right->left != NULL)
        recursive2(var, tree->right);
    dup2(copia_0, 0);
    dup2(copia_1, 1);
}

void make_binnary_tree(t_var *var, char *line)
{
    t_info_tree *tmp = init_struct_tree();
	
    var->tree = tmp;
    line = expansion(var, line);
    recursive_tree(var, tmp, line);
    tmp = var->tree;
    recursive2(var, tmp);
    tmp = var->tree;
    free_binnarytree(tmp);
}

#include "../includes/minishell.h"

char *save_sentence_l(char *string, int num)
{
    int i = 0;
    int j = 0;
    char *sentence = calloc((num + 100), sizeof(char));
    char *final;
    while (valid_chars(string[i]) || string[i] == ' ')
        i++;
    while (i < num && string[i] != '\0') {
        sentence[j] = string[i];
        i++;
        j++;
    }
    sentence[i] = '\0';
    final = ft_strtrim(sentence, " \t\n");
    free(sentence);
    return (final);
}

char *save_sentence_r(char *string, int num)
{
    int i = num;
    int j = 0;
    char *sentence = calloc((strlen(string) - num + 1), sizeof(char));
    char *final;
    while (string[i] && valid_chars(string[i]))
        i++;
    while (string[i] != '\0') {
        sentence[j] = string[i];
        i++;
        j++;
    }
    sentence[j] = '\0';
    final = ft_strtrim(sentence, " \t\n");
    free(sentence);
    return (final);
}

void    check_operator(t_info_tree *tree)
{
    if (ft_strlen(tree->operator) > 2)
        stx_error_op(WRONG_OP, tree->operator[0]);
    else if (tree->operator != NULL && ((!tree->left->command[0] && ft_strcmp(tree->operator, "<<") != 0) || !tree->right->command[0]))
        stx_error(WRONG_OP_NL);    
}

bool	ft_replace_chrchr(char *str, char find, char replace)
{
	int		i;
	bool	n;

	i = 0;
	n = false;
	while (str[i])
	{
		if (str[i] == find)
		{
			str[i] = replace;
			n = true;
		}
		i++;
	}
	return (n);
}

void	ft_remove_chr(char *str, char find)
{
	int		i;
    int     j;
	bool	n;

	i = 0;
    j = 0;
	n = false;

    if (str == NULL)
        return;
	while (str[i])
	{
		if (str[i] == find)
			i++;
        else
        {
            str[j] = str[i];
		    j++;
            i++;
        }
	}
    str[j] = '\0';
}

char *ft_replace_strstr(char *string, int index, int len, char *replace)
{
    int j = 0;
    int i = 0;

    char *new = malloc(sizeof(char) * (ft_strlen(string) + ft_strlen(replace) - len + 1));
    while (string[i] && i < index)
    {
        new[j] = string[i];
        j++;
        i++;
    }
    i += len + 1;
    if (replace && replace[0])
    {
        while (*replace)
            new[j++] = *replace++;
    }
    while (string[i])
        new[j++] = string[i++];
    new[j] = '\0';
    free(string);
    return(new);
}

#include "../includes/minishell.h"

t_env	*ft_lstnew_env(void *name, char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->name = name;
	node->end_type = 0;
	node->value = value;
	node->prev = NULL;
	node->next = NULL;
	return (node);
}

t_env *find_in_env(t_env *lst, char *name)
{
	t_env *tmp = lst;

	while (tmp)
	{

		if (ft_strcmp(tmp->name, name) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

t_env	*ft_lstlast_env(t_env *lst)
{
	t_env	*temp;

	temp = lst;
	if (!lst)
		return (NULL);
	while (temp->next)
		temp = temp->next;
	return (temp);
}

void ft_lstdelone_env(t_env **lst, t_env *todelate)
{
    if (!lst || !todelate)
        return;

    if (todelate == *lst)
    {
        *lst = todelate->next;
        if (*lst)
            (*lst)->prev = NULL;
    }
    else
    {
        todelate->prev->next = todelate->next;
        if (todelate->next)
            todelate->next->prev = todelate->prev;
    }

    free(todelate->name);
    free(todelate->value);
    free(todelate);
}

void	ft_lstadd_back_env(t_env **lst, t_env *new)
{
	t_env	*temp;

	if (lst != NULL)
	{
		if ((*lst) == NULL)
			*lst = new;
		else
		{
			temp = ft_lstlast_env(*lst);
			new->prev = temp;
			temp->next = new;
		}
	}
}

void	add_in_env(t_var *var, char *name, char *value)
{
	t_env *new;
	
	new = ft_lstnew_env(name, value);
	ft_lstadd_back_env(&var->env, new);
}

void save_env(t_var *var, char **env)
{
	int i = 0;
	var->env = NULL;
	t_env *new;
	char **arr;

    while (env[i])
	{
		arr = ft_split(env[i], '=');
		new = ft_lstnew_env(ft_strdup(arr[0]), ft_strdup(arr[1]));
		ft_lstadd_back_env(&var->env, new);
		free_arr(arr);
		i++;
	}
}

#include "../includes/minishell.h"

void    exec_error(char *command, char *error_msg)
{
    int fd;
    //char *s;
    
    fd = dup(1);
    dup2(2, 1);
    printf("%s: %s", command, error_msg);
    dup2(fd, 1);
}

void    stx_error(char *error_msg)
{
    int fd;
    //char *s;
    
    fd = dup(1);
    dup2(2, 1);
    printf("%s", error_msg);
    dup2(fd, 1);
}

void    stx_error_op(char *error_msg, char op)
{
    int fd;
    //char *s;
    
    fd = dup(1);
    dup2(2, 1);
    printf("%s '%c'\n", error_msg, op);
    dup2(fd, 1);
}

#include "../includes/minishell.h"

void free_lst(t_env* head) 
{
    t_env* current = head;
    t_env* next;

    while (current != NULL) {
        next = current->next;
        free(current->name);
        free(current->value);
        free(current);
        current = next;
    }
}

void free_binnarytree(t_info_tree *tree)
{
    if (!tree)
        return;
    free_binnarytree(tree->left);
    free_binnarytree(tree->right);

    if (tree->command)
        free(tree->command);
    if (tree->operator)
        free(tree->operator);
    free(tree);
}


void    func_exit(t_var *var)
{
    free_lst(var->env);
    free(var->act);
    free(var->op);
    free(var);
}



#include "../includes/minishell.h"

int	init_loop(char **argv, char **env)
{
    (void)argv;
	char *line = NULL;
	char *line_cleaned;
	char *previous_str;
    char *path;
    t_var *var = init_struct(env);
    previous_str = NULL;
   
	while(1)
	{
        init_signals(READ);
        path = get_cwd(var);
		line = readline(path);
        line_cleaned = NULL;
		update_signal(var->env);
        free(path);
        if (line && line[0] != '\0')
        {
		    line_cleaned = ft_strtrim(line, " \t\n");
		    manage_history(line_cleaned, &previous_str);
        }
		update_signal(var->env);
		make_binnary_tree(var, line_cleaned);
		free(line);
	}
    if (previous_str)
        free(previous_str);
	rl_clear_history();
    func_exit(var);
    return 0;
}


int main(int argc, char **argv, char **env) 
{
	(void)argv;

	g_exit_sig = 0;
	if (argc == 1)
	{
		init_loop(argv, env);
	}
	return (EXIT_SUCCESS);
}