/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_selector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseivane <oseivane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:28:30 by oseivane          #+#    #+#             */
/*   Updated: 2024/04/29 14:28:33 by oseivane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	save_actions_op(t_var *var)
{
	var->op = malloc(sizeof(t_actions_op) * NUM_ACTIONS + 1);
	var->op[0].action = ">";
	var->op[0].function = &ft_redirection_out;
	var->op[1].action = ">>";
	var->op[1].function = &ft_doubleredirection_out;
	var->op[2].action = "<";
	var->op[2].function = &ft_redirection_in;
	var->op[3].action = "<<";
	var->op[3].function = &ft_doubleredirection_in;
	var->op[4].action = ";";
	var->op[4].function = &ft_semicolon;
	var->op[5].action = NULL;
}

void	function_ptr_op(t_var *var, t_info_tree *tree)
{
	int	i;

	i = 0;
	while (var->op[i].action)
	{
		if (ft_strcmp(tree->operator, var->op[i].action) == 0)
		{
			(*(var->op[i].function))(var, tree);
			break ;
		}
		i++;
	}
}

void	save_actions(t_var *var)
{
	var->act = malloc(sizeof(t_actions) * NUM_ACTIONS + 1);
	var->act[0].action = EXIT;
	var->act[0].function = &ft_exit;
	var->act[1].action = ECHO;
	var->act[1].function = &ft_echo;
	var->act[2].action = PWD;
	var->act[2].function = &ft_pwd;
	var->act[3].action = CD;
	var->act[3].function = &ft_cd;
	var->act[4].action = EXPORT;
	var->act[4].function = &ft_export;
	var->act[5].action = UNSET;
	var->act[5].function = &ft_unset;
	var->act[6].action = ENV;
	var->act[6].function = &ft_env;
	var->act[7].action = HELP;
	var->act[7].function = &ft_help;
	var->act[8].action = NULL;
}

void	function_ptr(t_var *var, char **params)
{
	int	i;

	i = 0;
	while (var->act[i].action)
	{
		if (ft_strcmp(params[0], var->act[i].action) == 0)
		{
			(*(var->act[i].function))(var, params);
			break ;
		}
		i++;
	}
	if (!var->act[i].action)
		execute_action(var, params);
}
