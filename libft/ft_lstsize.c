/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 19:08:10 by mcatalan@st       #+#    #+#             */
/*   Updated: 2023/04/04 19:08:41 by mcatalan@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	unsigned int	length;
	t_list			*temp;

	temp = lst;
	length = 0;
	while (temp != NULL)
	{
		temp = temp->next;
		length++;
	}
	return (length);
}
