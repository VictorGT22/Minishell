/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vics <vics@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 17:52:30 by vics              #+#    #+#             */
/*   Updated: 2024/02/04 19:47:10 by vics             ###   ########.fr       */
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
    else if (tree->operator != NULL && (!tree->left->command[0] || !tree->right->command[0]))
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
                value_str = env->value;
            command = ft_replace_strstr(command, i - len - 1, len, value_str);
            last = i - ft_strlen(value_str);
            value_str = "";
        }
        len = 0;
    }
    return(command);
    //printf("%s\n", command);
}

void recursive_tree(t_var *var, t_info_tree *tree, char *string)
{
    int j = get_biggest_priority(string);

    if (j == -1) {
        tree->left = NULL;
        tree->right = NULL;
        tree->command = string;
        ft_remove_chr(tree->command, '"');
        ft_remove_chr(tree->command, '\'');
        //printf("command: %s\n", tree->command);
        
    } else {
        tree->command = NULL;
        tree->operator = get_operator(string, j);
		//printf("priority op: %s\n", tree->operator);
        tree->left = init_linked_tree(save_sentence_l(string, j), get_operator(string, j), tree->operator);
        tree->right = init_linked_tree(save_sentence_r(string, j), get_operator(string, j), tree->operator);
        check_operator(tree);
        ft_remove_chr(tree->left->command, '"');
        ft_remove_chr(tree->left->command, '\'');
		//printf("comando izquierda: %s\n", tree->left->command);
        ft_remove_chr(tree->right->command, '"');
        ft_remove_chr(tree->right->command, '\'');
		//printf("comando derecha: %s\n", tree->right->command);
        recursive_tree(var, tree->left, tree->left->command);
        recursive_tree(var, tree->right, tree->right->command);
    }
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

void recursive2(t_var *var, t_info_tree *tree)
{
    if (tree->operator != NULL)
	{
		printf("..Commando izq: %s\n", tree->left->command);
		printf("..Commando derecha: %s\n", tree->right->command);
		printf("..operador: %s\n", tree->operator);
	}
    if (tree->left != NULL && tree->left->left != NULL)
        recursive2(var, tree->left);
    if (tree->operator == NULL)
    {
		//printf("%s\n", tree->command);
        char **params = malloc(sizeof(char *) * 3);
        params[0] = save_command(tree->command);
        params[1] = save_params(tree->command);
        params[2] = NULL;
        
       // printf("command:%s\nparam:#%s#\n", params[0], params[1]);
        function_ptr(var, params);
    }
    if (tree->right != NULL && tree->right->left != NULL)
        recursive2(var, tree->right);
}

void make_binnary_tree(t_var *var, char *line)
{
    t_info_tree *tmp = init_struct_tree();
	
    var->tree = tmp;
    line = expansion(var, line);
    recursive_tree(var, tmp, line);
    tmp = var->tree;
    recursive2(var, tmp);
}

int main(int argc, char **argv, char **env) {
    char *line;
	char *line_cleaned;
	char *previous_str;
    t_var *var = init_struct(env);
    previous_str = NULL;
   
	while(1)
	{
		line = readline(get_cwd(var));
        if (line && line[0] != '\0')
        {
		    line_cleaned = ft_strtrim(line, " \t\n");
		    manage_history(line_cleaned, &previous_str);
        }
		make_binnary_tree(var, line_cleaned);
        
		free(line);
	}
	rl_clear_history();
    return 0;
}


 /* esto mejor si lo pones en una funcion de init_singnals por ejemplo asi el main queda mas limpio :)
    if (signal(SIGINT, sigintHandler) == SIG_ERR)
    {
        printf ("Error al configurar el handler de SIGINT");
        exit(EXIT_FAILURE);
    }
    if (signal(SIGQUIT, sigquitHandler) == SIG_ERR)
    {
        printf ("Error al configurar el handler de SIGQUIT");
        exit(EXIT_FAILURE);
    }
    */