#include "../includes/minishell.h"

void	exec_error(char *command, char *error_msg)
{
	int	fd;
	//char	*s;

	fd = dup(1);
	dup2(2, 1);
	printf("%s: %s", command, error_msg);
	dup2(fd, 1);
}

void	stx_error(char *error_msg)
{
	int	fd;
	//char *s;

	fd = dup(1);
	dup2(2, 1);
	printf("%s", error_msg);
	dup2(fd, 1);
}

void	stx_error_op(char *error_msg, char op)
{
	int	fd;
	//char *s;

	fd = dup(1);
	dup2(2, 1);
	printf("%s '%c'\n", error_msg, op);
	dup2(fd, 1);
}
