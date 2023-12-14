/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_num_size.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 13:01:54 by mcatalan@st       #+#    #+#             */
/*   Updated: 2023/04/04 13:02:39 by mcatalan@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_num_size(int num)
{
	unsigned int	len;

	len = 0;
	if (num == 0)
		return (1);
	if (num < 0)
		len += 1;
	while (num != 0)
	{
		num /= 10;
		len++;
	}
	return (len);
}
