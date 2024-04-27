#include "../includes/minishell.h"


/*
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

void    check_operator(t_info_tree *tree)
{
    if (ft_strlen(tree->operator) > 2)
        stx_error_op(WRONG_OP, tree->operator[0]);
    else if (tree->operator != NULL && ((!tree->left->command[0] && ft_strcmp(tree->operator, "<<") != 0) || !tree->right->command[0]))
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

    if (str == NULL)
        return;
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
}*/