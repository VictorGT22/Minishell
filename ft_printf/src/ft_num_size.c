/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_num_size.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan <mcatalan@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 18:40:43 by mcatalan@st       #+#    #+#             */
/*   Updated: 2023/07/07 10:22:49 by mcatalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

unsigned int	ft_number_size(unsigned long long nb)
{
	unsigned long long	l;

	l = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
		l += 1;
	while (nb != 0)
	{
		nb /= 10;
		l++;
	}
	return (l);
}
