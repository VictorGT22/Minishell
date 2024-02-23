#include "../includes/minishell.h"

void init_pipes_func(t_pipe *struct_pipes)
{
    int i = 0;

    struct_pipes->pipes = malloc(sizeof(int *) * struct_pipes->num_pipes);
    for (i = 0; i < struct_pipes->num_pipes; i++)
        struct_pipes->pipes[i] = malloc(sizeof(int) * 2);
    struct_pipes->save = dup(1);
}

void dup_functions(int i, int pipes_nbr, int save, int **pipes)
{
    if (i + 1 < pipes_nbr)
        dup2(pipes[i][1], 1);
    else
        dup2(save, 1);
    if (i != 0) {
        dup2(pipes[i - 1][0], 0);
        close(pipes[i - 1][1]);
    }
}

void pipes_func_ext(t_var *var, int i, t_pipe *struct_pipes, char **commands_arr)
{
    //int wstatus = -1;
    
    char *str = ft_strtrim(commands_arr[i], " \t");
    char **params = malloc(sizeof(char *) * 3);
    params[0] = save_command(str);
    params[1] = save_params(str);
    params[2] = NULL;
    dup_functions(i, struct_pipes->num_pipes, struct_pipes->save, struct_pipes->pipes);
    function_ptr(var, params);
	free(str);
	free_arr(params);
}

int func_pipe(t_var *var, char *command)
{
    char **commands_arr;
    //int num_pipes;
    t_pipe *struct_pipes = malloc(sizeof(t_pipe) * 1);
    
    if (!command)
        return (-1);
    commands_arr = ft_split(command, '|');
    struct_pipes->num_pipes = ft_arrlen(commands_arr); 
    init_pipes_func(struct_pipes);
    for(int i = 0; i < struct_pipes->num_pipes; i++)
        if (pipe(struct_pipes->pipes[i]) == -1)
            return (84);
    for (int i = 0; i < struct_pipes->num_pipes; i++)
        pipes_func_ext(var, i, struct_pipes, commands_arr);
	for (int i = 0; i < struct_pipes->num_pipes; i++)
        free(struct_pipes->pipes[i]);
	free_arr(commands_arr);
	free(struct_pipes->pipes);
	free(struct_pipes);
	return (0);   
}