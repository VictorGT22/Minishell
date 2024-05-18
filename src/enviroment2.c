/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseivane <oseivane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 10:41:32 by oseivane          #+#    #+#             */
/*   Updated: 2024/05/13 12:54:37 by oseivane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*find_in_env(t_env *lst, char *name)
{
	t_env	*tmp;

	tmp = lst;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, name) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}


void	ft_lstdelone_env(t_env **lst, t_env *todelate)
{
	if (!lst || !todelate)
		return ;
	if (todelate == *lst)
	{
		*lst = todelate->next;
		if (*lst)
			(*lst)->prev = NULL;
	}
	else
	{
		todelate->prev->next = todelate->next;
		if (todelate->next)
			todelate->next->prev = todelate->prev;
	}
	free(todelate->name);
	free(todelate->value);
	free(todelate);
}

void	add_in_env(t_var *var, char *name, char *value)
{
	t_env	*new;

	new = ft_lstnew_env(name, value);
	ft_lstadd_back_env(&var->env, new);
}
