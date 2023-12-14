/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_m.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:49:22 by mcatalan@st       #+#    #+#             */
/*   Updated: 2023/07/05 18:59:25 by mcatalan@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_putstr_m(char *str)
{
	int	i;
	int	error;

	i = 0;
	if (str == NULL)
		str = "(null)";
	while (str[i] != '\0')
	{
		error = ft_putchar_m(str[i]);
		if (error == -1)
			return (error);
		i++;
	}
	return (i);
}
