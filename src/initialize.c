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