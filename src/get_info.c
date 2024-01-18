#include "../includes/minishell.h"

int valid_chars(char n)
{
    if (n == '\0' || n == '\n' || n == '|'
    || n == '<' || n == ';' || n == '>'
    || n == '(' || n == ')' || n == '&')
        return 1;
    return 0;
}

int return_priority(char operator)
{
    if (operator == ')')
        return 3;
    if (operator == ';')
        return 2;
    if (operator == '<' || operator == '>' || operator == '|' || operator == '&')
        return 1;
    return (-1);
}

char *get_operator(char *string, int j)
{
    int i = 0;
    char *operator = malloc(sizeof(char) * 3);

    while (valid_chars(string[j])) {
        operator[i] = string[j];
        i++;
        j++;
    }
    operator[i] = '\0';
    return (operator);
}

int get_biggest_priority(char *string)
{
    int i = 0;
    int pos = -1;
    int biggest = -1;

    while (string[i] != '\0') {
        if (return_priority(string[i]) > biggest) {
            biggest = return_priority(string[i]);
            pos = i;
        }
        i++;
    }
	return (pos);
}