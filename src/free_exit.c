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