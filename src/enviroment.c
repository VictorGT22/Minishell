/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseivane <oseivane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:35:03 by oseivane          #+#    #+#             */
/*   Updated: 2024/04/29 14:42:54 by oseivane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*ft_lstnew_env(void *name, char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->name = name;
	node->value = value;
	node->prev = NULL;
	node->next = NULL;
	return (node);
}

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

t_env	*ft_lstlast_env(t_env *lst)
{
	t_env	*temp;

	temp = lst;
	if (!lst)
		return (NULL);
	while (temp->next)
		temp = temp->next;
	return (temp);
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

void	ft_lstadd_back_env(t_env **lst, t_env *new)
{
	t_env	*temp;

	if (lst != NULL)
	{
		if ((*lst) == NULL)
			*lst = new;
		else
		{
			temp = ft_lstlast_env(*lst);
			new->prev = temp;
			temp->next = new;
		}
	}
}

void	add_in_env(t_var *var, char *name, char *value)
{
	t_env	*new;

	new = ft_lstnew_env(name, value);
	ft_lstadd_back_env(&var->env, new);
}

void	save_env(t_var *var, char **env)
{
	int		i;
	t_env	*new;
	char	**arr;

	i = 0;
	var->env = NULL;
	while (env[i])
	{
		arr = ft_split(env[i], '=');
		new = ft_lstnew_env(ft_strdup(arr[0]), ft_strdup(arr[1]));
		ft_lstadd_back_env(&var->env, new);
		free_arr(arr);
		i++;
	}
}
