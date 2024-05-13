/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseivane <oseivane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:35:03 by oseivane          #+#    #+#             */
/*   Updated: 2024/05/13 10:46:57 by oseivane         ###   ########.fr       */
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