/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vics <vics@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 17:52:30 by vics              #+#    #+#             */
/*   Updated: 2024/01/17 16:54:22 by vics             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *save_sentence_l(char *string, int num)
{
    int i = 0;
    int j = 0;
    char *sentence = calloc((num + 100), sizeof(char));
    while (valid_chars(string[i]) || string[i] == ' ')
        i++;
    while (i < num && string[i] != '\0') {
        sentence[j] = string[i];
        i++;
        j++;
    }
    sentence[i] = '\0';
    return (sentence);
}

char *save_sentence_r(char *string, int num)
{
    int i = num;
    int j = 0;
    char *sentence = calloc((strlen(string) - num + 1), sizeof(char));

    while (valid_chars(string[i]))
        i++;
    while (string[i] != '\0') {
        sentence[j] = string[i];
        i++;
        j++;
    }
    sentence[j] = '\0';
    return (sentence);
}

void recursive_tree(t_info_tree *tree, char *string)
{
    int j = get_biggest_priority(string);

    if (j == -1) {
        tree->left = NULL;
        tree->right = NULL;
        tree->command = string;
    } else {
        tree->command = NULL;
        tree->operator = get_operator(string, j);
		printf("priority op: %s\n", tree->operator);
        tree->left = init_linked_tree(save_sentence_l(string, j), get_operator(string, j), tree->operator);
        tree->right = init_linked_tree(save_sentence_r(string, j), get_operator(string, j), tree->operator);
		printf("comando izquierda: %s\n", tree->left->command);
		printf("comando derecha: %s\n", tree->right->command);
        recursive_tree(tree->left, tree->left->command);
        recursive_tree(tree->right, tree->right->command);
    }
}

void recursive2(t_var *all, t_info_tree *tree)
{
    if (tree->operator != NULL)
	{
		printf("Commando izq: %s\n", tree->left->command);
		printf("Commando derecha: %s\n", tree->right->command);
		printf("operador: %s\n", tree->operator);
	}
    if (tree->left != NULL && tree->left->left != NULL)
        recursive2(all, tree->left);
    if (tree->operator == NULL)
		printf("%s\n", tree->command);
    if (tree->right != NULL && tree->right->left != NULL)
        recursive2(all, tree->right);
}

void make_binnary_tree(t_var *var, char *line)
{
    t_info_tree *tmp = init_struct_tree();
	
    var->tree = tmp;
    recursive_tree(tmp, line);
    tmp = var->tree;

	
	printf("\n\n\n");
	printf("%s\n", tmp->operator);
	printf("%s\n", tmp->left->command);
	printf("\n\n\n");
    recursive2(var, tmp);
}

int main() {
    char *line;
	char *line_cleaned;
	char *previous_str;
    t_var *var = init_struct();
	
	//char cwd[PATH_MAX];

	previous_str = NULL;
	while(1)
	{
		line = readline(get_cwd());
		line_cleaned = ft_strtrim(line, " \t\n");
		manage_history(line_cleaned, &previous_str);
		make_binnary_tree(var, line_cleaned);
		free(line);
	}
	clear_history();
    return 0;
}