/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 19:17:19 by mcatalan@st       #+#    #+#             */
/*   Updated: 2023/04/24 18:24:56 by mcatalan@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*temp;
	void	*tmp2;

	if (!f || !del || !lst)
		return (NULL);
	new_lst = NULL;
	while (lst)
	{
		tmp2 = f(lst->content);
		temp = ft_lstnew(tmp2);
		if (temp == NULL)
		{
			ft_lstclear(&new_lst, del);
			del(tmp2);
			return (NULL);
		}
		ft_lstadd_back(&new_lst, temp);
		lst = lst->next;
	}
	return (new_lst);
}
