#include "../includes/minishell.h"

int valid_chars(char n)
{
    if (n == '\0' || n == '\n'
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
    if (operator == '<' || operator == '>' || operator == '&')
        return 1;
    return (-1);
}

int len_operator(char *str, int i)
{
    char c = str[i];
    int len = 0;
    while(str[i] && str[i] == c)
    {
        i++;
        len++;
    }
    return (len);
}

char *get_operator(char *string, int j)
{
    int i = 0;
    int len = len_operator(string, j);
    char *operator = malloc(sizeof(char) * len + 1);

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
    char c = '\0';
    int pos = -1;
    int biggest = -1;

    if (string == NULL)
        return (-1);
    while (string[i] != '\0') {
        if (string[i] == '"' || string[i] == '\'')
        {
            if (c)
                c = '\0';
            else
                c = string[i];
        }
        if (return_priority(string[i]) > biggest && !c) {
            biggest = return_priority(string[i]);
            pos = i;
        }
        i++;
    }
	return (pos);
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
