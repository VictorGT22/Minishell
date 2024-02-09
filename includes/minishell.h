/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vics <vics@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 11:29:03 by mcatalan@st       #+#    #+#             */
/*   Updated: 2024/02/09 17:28:16 by vics             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <signal.h>
# include <sys/types.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <limits.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <linux/limits.h>
#include <sys/wait.h>
# include "../libft/libft.h"

//COLORS
#define BLUE "\033[0;34m"
#define GREEN "\033[0;32m"
#define RESET "\033[0m"

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

//COLORS
void blue(void);
void red(void);
void purple(void);
void yellow(void);
void green(void);
void resetColor(void);

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

//INITIALIZE
t_var *init_struct(char **env);
t_info_tree *init_linked_tree(char *command, char *operator, char *prev_op);
t_info_tree *init_struct_tree(void);

//ENVIROMENT
void save_env(t_var *var, char **env);
t_env *find_in_env(t_env *lst, char *name);
void	add_in_env(t_var *var, char *name, char *value);
void ft_lstdelone_env(t_env **lst, t_env *todelate);

//INPUT
char 	*get_cwd();
void	manage_history(char *line, char **previous_str);

//UTILS
int		valid_chars(char n);
char	*ft_strcat(char *dest, char *src);

//GET INFORMATION
int 	get_biggest_priority(char *string);
char	*get_operator(char *string, int j);
char	*save_params(char *str);
char	*save_command(char *str);

//MANAGE SIGNALS
void    sigintHandler(int signal);
void    sigquitHandler(int signal);

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

//PIPES
int		func_pipe(t_var *var, char *command);

#endif