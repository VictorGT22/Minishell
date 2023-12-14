/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ft_p_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 19:02:43 by mcatalan@st       #+#    #+#             */
/*   Updated: 2023/07/05 20:16:55 by mcatalan@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void	*ft_ext_convert_ptr(unsigned long long nb, char *str, char *b)
{
	if (nb >= (unsigned long long)ft_strlen(b))
	{
		ft_ext_convert_ptr(nb / ft_strlen(b), str, b);
		ft_ext_convert_ptr(nb % ft_strlen(b), str, b);
	}
	else
		ft_add_str(str, b[nb]);
	return (str);
}

char	*ft_convert_ptr(unsigned long long nb, char *b)
{
	unsigned long long	nb2;
	int					l;
	char				*str;

	nb2 = (unsigned long long)nb;
	l = ft_number_size(nb);
	str = malloc(sizeof(char) * (l + 1));
	if (str == NULL)
		return (NULL);
	ft_bzero(str, (size_t)l + 1);
	ft_ext_convert_ptr(nb2, str, b);
	return (str);
}

int	ft_p_ptr(void *ptr)
{
	char	*str;
	char	*n;
	int		l;

	str = ft_convert_ptr((unsigned long long)ptr, "0123456789abcdef");
	if (str == NULL)
	{
		free(str);
		return (-1);
	}
	n = ft_strjoin("0x", str);
	if (n == NULL)
	{
		free(n);
		if (str)
			free(str);
		return (-1);
	}
	l = ft_putstr_m(n);
	free(str);
	free(n);
	return (l);
}
