/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vics <vics@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 17:52:30 by vics              #+#    #+#             */
/*   Updated: 2024/04/13 19:06:30 by vics             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void    exec_error(char *command, char *error_msg)
{
    int fd;
    char *s;
    
    fd = dup(1);
    dup2(2, 1);
    printf("%s: %s", command, error_msg);
    dup2(fd, 1);
}

void    stx_error(char *error_msg)
{
    int fd;
    char *s;
    
    fd = dup(1);
    dup2(2, 1);
    printf("%s", error_msg);
    dup2(fd, 1);
}

void    stx_error_op(char *error_msg, char op)
{
    int fd;
    char *s;
    
    fd = dup(1);
    dup2(2, 1);
    printf("%s '%c'\n", error_msg, op);
    dup2(fd, 1);
}

void    check_operator(t_info_tree *tree)
{
    if (ft_strlen(tree->operator) > 2)
        stx_error_op(WRONG_OP, tree->operator[0]);
    else if (tree->operator != NULL && (!tree->left->command[0] && ft_strcmp(tree->operator, "<<") != 0 || !tree->right->command[0]))
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

char	*remove_extra_spaces(char *str)
{
	int j;
	int	x;
	char *final;
	
	j = 0;
	x = 0;
	final = malloc(sizeof(char) * ft_strlen(str) + 1);
	ft_bzero(final, ft_strlen(str) + 1);
	while (str[j] && (str[j] == ' ' || str[j] == '\t'))
		j++;
	while (str[j])
	{
		if ((str[j] != ' ' && str[j] != '\t')
		|| (str[j + 1] != ' ' && str[j + 1] != '\t'))
			final[x++] = str[j];
		j++;
	}
	return (final);
}

char *get_name(t_var *var, char *command, int start, int len)
{
    char *name;
    t_env *env = NULL;
    
    name = malloc(sizeof(char) * len + 1);
    name = ft_substr(command, start, len);
    env = find_in_env(var->env, name);
    free(name);
    if (env)
        return (remove_extra_spaces(env->value));
    return (NULL);
}

void expand(t_var *var, char **command, int index)
{
    int i = index + 1;
    int len = 0;
    char *value_str;
    
    while ((*command)[i] && (ft_isalnum((*command)[i]) || (*command)[i] == '.' || (*command)[i] == '?')) {
        i++;
        len++;
    }
    value_str = get_name(var, *command, index + 1, len); 
    if (!value_str) {
        if (!ft_isalnum((*command)[index + 1])) {
            if ((*command)[index + 1] == '$') {
                value_str = ft_strdup("4752");
                len = 1;
            }
            else if ((*command)[index + 1] == '?')
                value_str = ft_strdup("0");
            else if ((*command)[index + 1] == '.')
                value_str = ft_substr(*command, index, len);
        }           
        else if (!ft_isalpha((*command)[index + 1]))
            value_str = ft_substr(*command, index + 2, len - 1);
        else
            value_str = ft_strdup("");
    }
    if (value_str) {
        *command = ft_replace_strstr(*command, index, len, value_str);
        free(value_str);
    }
}

char *expansion_var(t_var *var, char *command)
{
    int i = 0;
    while (command[i])
    {
        if (command[i] == '\'')
        {
            i++;
            while (command[i] && command[i] != '\'')
                i++;
        }
        if (command[i] && command[i] == '$')
            expand(var, &command, i);
        i++;
    }
    return (command);
}

void    remove_quote(char **str)
{
    int i = 0;
    int j = 0;
    char c = '\0';

    while ((*str)[i])
    {
        if ((*str)[i] == '\'' || (*str)[i] == '"')
        {
            c = (*str)[i];
            i++;            
        }
        else
            (*str)[j++] = (*str)[i];
        while (c && (*str)[i])
        {
            if ((*str)[i] == c)
                break;
            (*str)[j++] = (*str)[i++];
        }
        if (!(*str)[i] && c)
        {
            (*str) = NULL;
            break;
        }
        c = '\0';
        i++;
    }
    if (*str)
        (*str)[j] = '\0';
}

void recursive_tree(t_var *var, t_info_tree *tree, char *string)
{
    int j = get_biggest_priority(string);

    if (j == -1) {
        tree->left = NULL;
        tree->right = NULL;
        tree->operator = NULL;
        tree->command = string;
    }
    else {
        tree->command = NULL;
        tree->operator = get_operator(string, j);
        tree->left = init_linked_tree(save_sentence_l(string, j), tree->operator, tree->operator);
        tree->right = init_linked_tree(save_sentence_r(string, j), tree->operator, tree->operator);
        // printf("operador: %s\n", tree->operator);
        // printf("left->command: %s\n", tree->left->command);
        // printf("right->command: %s\n", tree->right->command);
        check_operator(tree);
        remove_quote(&tree->left->command);
        remove_quote(&tree->right->command);
        recursive_tree(var, tree->left, tree->left->command);
        recursive_tree(var, tree->right, tree->right->command);
    }
}

void recursive2(t_var *var, t_info_tree *tree)
{
    int copia_0 = dup(0);
    int copia_1 = dup(1);

    if (tree->operator != NULL)
    {
        printf("operador: %s\n", tree->operator);
        printf("operador siguiente derecha: %s\n", tree->right->operator);
        printf("left->command: %s\n", tree->left->command);
        printf("right->command: %s\n", tree->right->command);
    }   //function_ptr_op(var, tree);
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
    line = expansion_var(var, line);
    remove_quote(&line);
    if (line)
    {
        recursive_tree(var, tmp, line);
        tmp = var->tree;
        recursive2(var, tmp);
        tmp = var->tree;
        free_binnarytree(tmp);
    }
    else
        printf("error quote!!!!\n");
}

void free_lst(t_env* head) {
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

int main(int argc, char **argv, char **env) {
    char *line = NULL;
	char *line_cleaned;
	char *previous_str;
    char *path;
    t_var *var = init_struct(env);
    previous_str = NULL;
   
   printf("ejecutando minishell!\n");
	while(1)
	{
        path = get_cwd(var);
		line = readline(path);
        line_cleaned = NULL;
        printf("entra bucle %d!\n", argc);
        free(path);
        if (line && line[0] != '\0')
        {
		    line_cleaned = ft_strtrim(line, " \t\n");
		    manage_history(line_cleaned, &previous_str);
            char **arr = ft_split(line_cleaned, ';');
            int i = 0;
            while (arr[i])
            {
		        make_binnary_tree(var, arr[i]);
                printf("fin\n\n");
                i++;
            }
        }
		free(line);
	}
    printf("se sale ejecucion\n");
    
    if (previous_str)
        free(previous_str);
	rl_clear_history();
    printf("se sale\n");
    func_exit(var);
    return 0;
}