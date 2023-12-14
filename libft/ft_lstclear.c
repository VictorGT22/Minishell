/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 19:15:12 by mcatalan@st       #+#    #+#             */
/*   Updated: 2023/04/04 19:15:39 by mcatalan@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*bor;

	if (!del || !lst)
		return ;
	while (*lst)
	{
		bor = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = bor;
	}
	*lst = NULL;
}
