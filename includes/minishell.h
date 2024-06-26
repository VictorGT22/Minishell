/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vics <vics@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 11:29:03 by mcatalan@st       #+#    #+#             */
/*   Updated: 2024/04/27 18:07:33 by vics             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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
// # include <readline/readline.h>
// # include <readline/history.h>
# include <limits.h>
#include <sys/wait.h>
# include "../libft/libft.h"
# include "../readline/readline.h"
# include "../readline/history.h"

//COLORS
#define BLUE "\033[0;34m"
#define GREEN "\033[0;32m"
#define RESET "\033[0m"

//SIGNAL MODES
# define READ		1
# define HEREDOC	2
# define EXEC		3

//GLOBAL VARIABLES
//int	g_exit_sig;

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
void	read_handler(int signal, siginfo_t *data, void *n_data);
void	heredoc_handler(int signal, siginfo_t *data, void *n_data);
void	exec_handler(int signal, siginfo_t *data, void *n_data);
void	init_signals(int mode);

//FUNCTION PTR
void    save_actions(t_var *var);
void    function_ptr(t_var *var, char **params, char *command, int *pipe);
void    save_actions_op(t_var *var);
void    function_ptr_op(t_var *var, t_info_tree *tree);

void    remove_quote(char **str);
char *expansion_var(t_var *var, char *command);

void	ft_echo(t_var *var, char **params);
void	ft_pwd(t_var *var, char **params);
void	update_oldpwd(t_var *var, char *newpwd);
void	change_path(t_var *var, char*param, char *path, char *old_path);
void	ft_cd(t_var *var, char **params);
void	print_env(t_var *var, char *str);
void	ft_exit(t_var *var, char **params);
char	*ft_strcat(char *dest, char *src);
char	*find_func(char **paths, char *function);
void	execute_action(t_var *var, char **params, int *pipe);
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