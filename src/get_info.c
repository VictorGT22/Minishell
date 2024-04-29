#include "../includes/minishell.h"

int	valid_chars(char n)
{
	if (n == '\0' || n == '\n'
		|| n == '<' || n == ';' || n == '>'
		|| n == '(' || n == ')' || n == '&')
		return (1);
	return (0);
}

int	return_priority(char operator)
{
	if (operator == ')')
		return (3);
	if (operator == ';')
		return (2);
	if (operator == '<' || operator == '>' || operator == '&')
		return (1);
	return (-1);
}

int	len_operator(char *str, int i)
{
	char	c;
	int		len;

	len = 0;
	c = str[i];
	while (str[i] && str[i] == c)
	{
		i++;
		len++;
	}
	return (len);
}

char	*get_operator(char *string, int j)
{
	int		i;
	int		len;
	char	*operator;

	i = 0;
	len = len_operator(string, j);
	operator = malloc(sizeof(char) * len + 1);
	if (!operator)
		return (NULL);
	while (valid_chars(string[j]))
		operator[i++] = string[j++];
	operator[i] = '\0';
	return (operator);
}

int	get_biggest_priority(char *string)
{
	int		i;
	char	c;
	int		pos;
	int		biggest;

	i = 0;
	c = '\0';
	pos = -1;
	biggest = -1;
	if (string == NULL)
		return (-1);
	while (string[i] != '\0')
	{
		if (string[i] == '"' || string[i] == '\'')
		{
			if (c)
				c = '\0';
			else
				c = string[i];
		}
		if (return_priority(string[i]) > biggest && !c)
		{
			biggest = return_priority(string[i]);
			pos = i;
		}
		i++;
	}
	return (pos);
}


char	*save_command(char *str)
{
	int		i;
	char	*command;

	i = 0;
	while (str[i] && str[i] != ' ')
		i++;
	command = malloc(sizeof(char) * i + 1);
	if (!command)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != ' ')
	{
		command[i] = str[i];
		i++;
	}
	command[i] = '\0';
	return (command);
}

char	*save_params(char *str)
{
	int		i;
	int		j;
	char	*param;

	i = 0;
	j = 0;
	while (str[i] && str[i] != ' ')
		i++;
	if (str[i] == ' ')
		i++;
	j = ft_strlen(&str[i]);
	param = malloc(sizeof(char) * j + 1);
	if (!param)
		return (NULL);
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
