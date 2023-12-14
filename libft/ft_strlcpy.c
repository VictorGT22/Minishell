/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 12:44:32 by mcatalan@st       #+#    #+#             */
/*   Updated: 2023/04/04 18:53:29 by mcatalan@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_strlcpy(char *dest, char *str, unsigned int size)
{
	unsigned int	i;

	i = 0;
	if (size != 0)
	{
		while (str[i] != '\0' && i < size - 1)
		{
			dest[i] = str[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (ft_strlen(str));
}
