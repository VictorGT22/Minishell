/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseivane <oseivane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:39:15 by oseivane          #+#    #+#             */
/*   Updated: 2024/05/18 17:54:24 by oseivane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

// Readline .h files
# include "../readline/readline.h"
# include "../readline/history.h"

// Our .h files
# include "../libft/libft.h"
# include "structs.h"
# include "definitions.h"

//GLOBAL VARIABLE

int wstatus;

//DISPLAYS
void		ft_printall(t_var *var);
char		*intToString(int num);
char		*toString_t_var(t_var *var);
char		*toString_t_env(t_env *env);
char		*toString_t_info_tree(t_info_tree *tree);

//INITIALIZE
int			init_loop(char **argv, char **env);
t_var		*init_struct(char **env);
t_info_tree	*init_linked_tree(char *command, char *operator, char *prev_op);
t_info_tree	*init_struct_tree(void);

//ENVIROMENT
void		save_env(t_var *var, char **env);
void		add_in_env(t_var *var, char *name, char *value);
void		ft_lstdelone_env(t_env **lst, t_env *todelate);
void		ft_lstadd_back_env(t_env **lst, t_env *new);
t_env		*ft_lstnew_env(void *name, char *value);
t_env		*ft_lstlast_env(t_env *lst);
t_env		*find_in_env(t_env *lst, char *name);

//INPUT
char		*get_cwd(t_var *var);
void		manage_history(char *line, char **previous_str);

//UTILS
int			valid_chars(char n);
char		*ft_strcat(char *dest, char *src);
void		func_exit(t_var *var);
char		*ft_newold(char *new, char *old);

//TREE OPERATIONS
bool		ft_replace_chrchr(char *str, char find, char replace);
char		*ft_replace_strstr(char *string, int index, int len, char *replace);
void		ft_remove_chr(char *str, char find);
char		*save_sentence_r(char *string, int num);
char		*save_sentence_l(char *string, int num);
void		check_operator(t_info_tree *tree);

//FREE
void		free_arr(char **arr);
void		free_binnarytree(t_info_tree *tree);
void		make_binnary_tree(t_var *var, char *line);

//GET INFORMATION
int			get_biggest_priority(char *string);
char		*get_operator(char *string, int j);
char		*save_params(char *str);
char		*save_command(char *str);

//SIGNALS
void		update_signal(t_env *env);
static void	read_handler(int signal, siginfo_t *data, void *n_data);
static void	heredoc_handler(int signal, siginfo_t *data, void *n_data);
static void	exec_handler(int signal, siginfo_t *data, void *n_data);
void		init_signals(int mode);

//BUILT-IN
void		save_actions(t_var *var);
void		function_ptr(t_var *var, char **params);

void		save_actions_op(t_var *var);
void		function_ptr_op(t_var *var, t_info_tree *tree);
void		ft_index(char **params, int index_dash, char *flag);
void		ft_echo(t_var *var, char **params);
void		ft_pwd(t_var *var, char **params);
void		update_oldpwd(t_var *var, char *newpwd);
void		change_path(t_var *var, char*param, char *path, char *old_path);
void		hyphen_case(t_var *var, char *path, char *old_path);
void		etc_case(char *path, char *old_path);
void		slash_case(char *path, char *old_path, char **params);
void		other_case(char *path, char *old_path, char **params);
void		ft_cd(t_var *var, char **params);
void		print_env(t_var *var, char *str);
void		ft_exit(t_var *var, char **params);
char		*ft_strcat(char *dest, char *src);
char		*find_func(char **paths, char *function);
void		exec_path(char *execution_path, char **params);
void		execute_action(t_var *var, char **params);
void		ft_unset(t_var *var, char**params);
void		ft_help(t_var *var, char **params);
void		get_add_var_env(t_var *var, char **params, int index);
void		ft_export(t_var *var, char **params);
void		ft_env(t_var *var, char **params);
void		ft_redirection_out(t_var *var, t_info_tree *tree);
void		ft_doubleredirection_out(t_var *var, t_info_tree *tree);
void		ft_redirection_in(t_var *var, t_info_tree *tree);
void		ft_doubleredirection_in(t_var *var, t_info_tree *tree);
void		ft_semicolon(t_var *var, t_info_tree *tree);

//ERROR
void		stx_error(char *error_msg);
void		exec_error(char *command, char *error_msg);
void		stx_error_op(char *error_msg, char op);

//PIPES
int			func_pipe(t_var *var, char *command);

#endif