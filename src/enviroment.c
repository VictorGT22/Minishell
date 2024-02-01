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

t_env *find_in_env(t_env *lst, char *name)
{
	t_env *tmp = lst;

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



void	ft_lstdelone_env(t_env *lst, void (*del)(void *))
{
	t_env	*temp;

	temp = lst;
	if (!lst || !del)
		return ;
	lst = lst->next;
	free(temp->name);
	free(temp->value);
	free(temp);
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
	t_env *new;
	
	new = ft_lstnew_env(name, value);
	ft_lstadd_back_env(&var->env, new);
}

void save_env(t_var *var, char **env)
{
	int i = 0;
	var->env = NULL;
	t_env *new;
	char **arr;

    while (env[i])
	{
		arr = ft_split(env[i], '=');
		new = ft_lstnew_env(arr[0], arr[1]);
		ft_lstadd_back_env(&var->env, new);
		i++;
	}
}
