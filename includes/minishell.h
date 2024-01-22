/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vics <vics@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 11:29:03 by mcatalan@st       #+#    #+#             */
/*   Updated: 2024/01/17 15:37:02 by vics             ###   ########.fr       */
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
# include "../libft/libft.h"

//COLORS
#define BLUE "\033[0;34m"
#define RESET "\033[0m"

void blue(void);
void resetColor(void);

//INPUT
char *get_cwd();
void	manage_history(char *line, char **previous_str);

//UTILS
int valid_chars(char n);


//GET INFORMATION
int get_biggest_priority(char *string);
char *get_operator(char *string, int j);

//MANAGE SIGNALS
void    sigintHandler(int signal);
void    sigquitHandler(int signal);

typedef struct s_info_tree {
	char *operator;
	char *prev_operator;
	char *command;
	int checked;
	struct s_info_tree *left;
	struct s_info_tree *right;
} t_info_tree;

typedef struct s_var {
	struct s_info_tree *tree;
} t_var;

//INITIALIZE
t_var *init_struct(void);
t_info_tree *init_linked_tree(char *command, char *operator, char *prev_op);
t_info_tree *init_struct_tree(void);

#endif