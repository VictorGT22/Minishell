/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 12:03:30 by mcatalan@st       #+#    #+#             */
/*   Updated: 2023/07/06 10:49:16 by mcatalan@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	filter_flags(char c, va_list args)
{
	if (c == 'c')
		return (ft_putchar_m(va_arg(args, int)));
	else if (c == '%')
		return (ft_putchar_m('%'));
	else if (c == 's')
		return (ft_putstr_m(va_arg(args, char *)));
	else if (c == 'd' || c == 'i')
		return (ft_p_nbr(va_arg(args, int)));
	else if (c == 'p')
		return (ft_p_ptr(va_arg(args, void *)));
	else if (c == 'u')
		return (ft_p_u(va_arg(args, unsigned int)));
	else if (c == 'x')
		return (ft_p_hex_min(va_arg(args, int)));
	else if (c == 'X')
		return (ft_p_hex_may(va_arg(args, int)));
	return (0);
}

int	read_str(const char *str, va_list args, int cc)
{
	int	i;
	int	check;

	i = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			check = filter_flags(str[i + 1], args);
			if (check != -1)
				cc += check;
			else
				return (-1);
			i++;
		}
		else
		{
			if (ft_putchar_m(str[i]) != 1)
				return (-1);
			cc++;
		}
		i++;
	}
	return (cc);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		cc;

	cc = 0;
	va_start(args, str);
	cc = read_str(str, args, cc);
	va_end(args);
	return (cc);
}
