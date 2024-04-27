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
            if (!name)
                return (NULL);
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