/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 14:09:43 by mcatalan@st       #+#    #+#             */
/*   Updated: 2023/05/02 19:25:56 by mcatalan@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* A function that allocates a block of memory and initializes it to zero.
With a given parameter and a given size of it */

void	*ft_calloc(size_t count, size_t size)
{
	size_t	b;
	void	*p;

	b = count * size;
	p = malloc(b);
	if (p == NULL)
	{
		return (NULL);
	}
	else
		ft_bzero(p, b);
	return (p);
}
