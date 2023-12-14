/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p_nbr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 12:35:04 by mcatalan          #+#    #+#             */
/*   Updated: 2023/07/06 10:54:05 by mcatalan@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_ext_convert_base(long int nb, char *str, char *b)
{
	if (nb < 0)
	{
		ft_add_str(str, '-');
		nb = -nb;
	}
	if (nb >= ft_strlen(b))
	{
		ft_ext_convert_base(nb / ft_strlen(b), str, b);
		ft_ext_convert_base(nb % ft_strlen(b), str, b);
	}
	else
	{
		ft_add_str(str, b[nb]);
	}
}

char	*ft_convert_base(int nb, char *b)
{
	long int	nb2;
	int			l;
	char		*str;

	nb2 = (long int)nb;
	l = ft_number_size(nb);
	str = malloc(sizeof(char) * (l + 1));
	if (str == NULL)
		return (NULL);
	ft_bzero(str, (size_t)l + 1);
	ft_ext_convert_base(nb2, str, b);
	return (str);
}

int	ft_p_nbr(int nb)
{
	char	*str;
	int		l;

	str = ft_convert_base(nb, "0123456789");
	if (str == NULL)
		return (-1);
	l = ft_putstr_m(str);
	free(str);
	return (l);
}
