/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseivane <oseivane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:35:45 by oseivane          #+#    #+#             */
/*   Updated: 2024/05/13 10:10:19 by oseivane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_pipes_func(t_pipe *struct_pipes)
{
	int	i;

	i = 0;
	struct_pipes->pipes = malloc(sizeof(int *) * struct_pipes->num_pipes);
	if (!struct_pipes->pipes)
		return ;
	for (i = 0; i < struct_pipes->num_pipes; i++)
		struct_pipes->pipes[i] = malloc(sizeof(int) * 2);
		if (!struct_pipes->pipes[i])
			return ;
	struct_pipes->save = dup(1);
}

void	dup_functions(int i, int pipes_nbr, int save, int **pipes)
{
	if (i + 1 < pipes_nbr)
		dup2(pipes[i][1], 1);
	else
		dup2(save, 1);
	if (i != 0)
	{
		dup2(pipes[i - 1][0], 0);
		close(pipes[i - 1][1]);
	}
}

void	pipes_func_ext(t_var *var, int i,
	t_pipe *struct_pipes, char **commands_arr)
{
	char	*str;
	char	**params;
	int		wstatus;

	wstatus = -1;
	str = ft_strtrim(commands_arr[i], " \t");
	params = malloc(sizeof(char *) * 3);
	if (!params)
		return ;
	params[0] = save_command(str);
	params[1] = save_params(str);
	params[2] = NULL;
	dup_functions(i, struct_pipes->num_pipes,
		struct_pipes->save, struct_pipes->pipes);
	function_ptr(var, params);
	free(str);
	free_arr(params);
}

int	func_pipe(t_var *var, char *command)
{
	char	**commands_arr;
	int		num_pipes;
	t_pipe	*struct_pipes;

	if (!command)
		return (-1);
	commands_arr = ft_split(command, '|');
	if (!commands_arr)
		return (-1);
	struct_pipes = malloc(sizeof(t_pipe));
	if (!struct_pipes)
	{
		free_arr(commands_arr);
		return (-1);
	}
	struct_pipes->num_pipes = ft_arrlen(commands_arr);
	if (struct_pipes->num_pipes <= 0)
	{
		free_arr(commands_arr);
		free(struct_pipes);
		return (-1);
	}
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
