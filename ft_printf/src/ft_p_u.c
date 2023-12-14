/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ft_p_u.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 19:02:58 by mcatalan@st       #+#    #+#             */
/*   Updated: 2023/07/05 20:18:32 by mcatalan@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void	ft_ext_convert_ubase(unsigned int nb, char *str, char *b)
{
	if (nb >= (unsigned int)ft_strlen(b))
	{
		ft_ext_convert_ubase(nb / ft_strlen(b), str, b);
		ft_ext_convert_ubase(nb % ft_strlen(b), str, b);
	}
	else
	{
		ft_add_str(str, b[nb]);
	}
}

char	*ft_convert_ubase(unsigned int nb, char *b)
{
	unsigned int	nb2;
	int				l;
	char			*str;

	nb2 = (unsigned int)nb;
	l = ft_number_size(nb);
	str = malloc(sizeof(char) * (l + 1));
	if (str == NULL)
		return (NULL);
	ft_bzero(str, (size_t)l + 1);
	ft_ext_convert_ubase(nb2, str, b);
	return (str);
}

int	ft_p_u(unsigned int nb)
{
	char	*str;
	int		l;

	str = ft_convert_ubase(nb, "0123456789");
	if (str == NULL)
		return (-1);
	l = ft_putstr_m(str);
	free(str);
	return (l);
}
