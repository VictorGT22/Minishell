/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 12:45:47 by mcatalan@st       #+#    #+#             */
/*   Updated: 2023/04/04 12:46:19 by mcatalan@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*str;

	if (!s)
		return (NULL);
	if ((unsigned int)ft_strlen((char *)s) < start)
	{
		len = 0;
		start = 0;
	}
	else if ((unsigned int)ft_strlen((char *)(s + start)) < len)
		len = ft_strlen((char *)(s + start));
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, (char *)(s + start), len + 1);
	return (str);
}
