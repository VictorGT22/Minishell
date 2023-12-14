/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 15:31:07 by mcatalan@st       #+#    #+#             */
/*   Updated: 2023/03/08 15:38:03 by mcatalan@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*x;
	unsigned char	*j;
	size_t			i;

	i = 0;
	x = (unsigned char *) dst;
	j = (unsigned char *) src;
	if (!dst && !src)
		return (NULL);
	while (i < n)
	{
		x[i] = j[i];
		i++;
	}
	return (x);
}
