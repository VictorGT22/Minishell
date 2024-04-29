/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseivane <oseivane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:23:42 by oseivane          #+#    #+#             */
/*   Updated: 2024/04/29 12:15:33 by oseivane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_printall(t_var *var)
{
    //printear s_info tree
    printf("----------se imprime estructura Tree--------\n");
    printf("operator: %s\n", var->tree->operator);
	printf("operator: %s\n", var->tree->prev_operator);
	printf("operator: %s\n", var->tree->command);
	printf("operator: %d\n", var->tree->checked);

	//printear env
    printf("----------se imprime estructura env--------\n");
    printf("operator: %s\n", var->env->name);
	printf("operator: %s\n", var->env->value);

	//printear actions
    printf("----------se imprime estructura actions--------\n");
    printf("operator: %s\n", var->act->action);
	printf("operator: %p\n", var->act->function);

	//printear actions_op
    printf("----------se imprime estructura actions_op--------\n");
    printf("operator: %s\n", var->op->action);
	printf("operator: %p\n", var->op->function);
}

#include "../includes/minishell.h"

// Función auxiliar para convertir un entero a una cadena de caracteres
char *intToString(int num) 
{
    char *str = malloc(sizeof(char) * 12); // Suficiente para almacenar cualquier entero
    snprintf(str, 12, "%d", num);
    return str;
}

// Función para convertir la estructura t_var a una cadena de caracteres
char *toString_t_var(t_var *var)
 {
    char *result = malloc(sizeof(char) * 1000); // Tamaño arbitrario para la cadena resultante

    // Comenzar la representación con información sobre la estructura t_var
    strcpy(result, "t_var:\n");

    // Representar la estructura t_env
    strcat(result, "t_env:\n");
    t_env *env = var->env;
    while (env != NULL) {
        strcat(result, env->name);
        strcat(result, ": ");
        strcat(result, env->value);
        strcat(result, "\n");
        env = env->next;
    }

    // Representar la estructura t_actions
    strcat(result, "t_actions:\n");
    t_actions *act = var->act;
    while (act != NULL && act->action != NULL) {
        strcat(result, act->action);
        strcat(result, "\n");
        act++;
    }

    // Representar la estructura t_actions_op
    strcat(result, "t_actions_op:\n");
    t_actions_op *op = var->op;
    while (op != NULL && op->action != NULL) {
        strcat(result, op->action);
        strcat(result, "\n");
        op++;
    }

    // Representar la estructura t_info_tree (árbol binario)
    strcat(result, "t_info_tree (Binary Tree):\n");
    // Aquí puedes incluir una función recursiva para representar el árbol binario
    
    return result;
}

// Función para convertir la estructura t_env a una cadena de caracteres
char *toString_t_env(t_env *env) 
{
    char *result = malloc(sizeof(char) * 100); // Tamaño arbitrario para la cadena resultante

    // Comenzar la representación con información sobre la estructura t_env
    strcpy(result, "t_env:\n");

    // Representar cada nodo de la lista enlazada
    while (env != NULL) {
        strcat(result, env->name);
        strcat(result, ": ");
        strcat(result, env->value);
        strcat(result, "\n");
        env = env->next;
    }

    return result;
}

// Función para convertir la estructura t_info_tree a una cadena de caracteres
char *toString_t_info_tree(t_info_tree *tree) 
{
    char *result = malloc(sizeof(char) * 100); // Tamaño arbitrario para la cadena resultante

    // Comenzar la representación con información sobre la estructura t_info_tree
    strcpy(result, "t_info_tree:\n");

    // Aquí puedes incluir una función recursiva para representar el árbol binario

    return result;
}

