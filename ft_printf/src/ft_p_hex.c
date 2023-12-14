/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p_hex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 19:02:23 by mcatalan@st       #+#    #+#             */
/*   Updated: 2023/07/06 11:06:48 by mcatalan@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_p_hex_may(int nb)
{
	char	*str;
	int		l;

	str = ft_convert_ubase(nb, "0123456789ABCDEF");
	if (str == NULL)
		return (-1);
	l = ft_putstr_m(str);
	free(str);
	return (l);
}

int	ft_p_hex_min(int nb)
{
	char	*str;
	int		l;

	str = ft_convert_ubase(nb, "0123456789abcdef");
	if (str == NULL)
		return (-1);
	l = ft_putstr_m(str);
	free(str);
	return (l);
}
