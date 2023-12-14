/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatalan@student.42barcelona.com <mcata    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 11:59:01 by mcatalan@st       #+#    #+#             */
/*   Updated: 2023/07/06 11:08:22 by mcatalan@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>

// ft_printf.c
int				ft_printf(const char *string, ...);

// ft_putchar_m.c
int				ft_putchar_m(char c);

// ft_putstr_m.c
int				ft_putstr_m(char *str);

// ft_p_nbr.c
int				ft_p_nbr(int nb);
char			*ft_convert_base(int nb, char *b);

// ft_p_ptr.c
int				ft_p_ptr(void *ptr);
char			*ft_convert_ptr(unsigned long long nb, char *b);

// ft_p_udec.c
int				ft_p_u(unsigned int nb);
char			*ft_convert_ubase(unsigned int n, char *base);

// ft_p_hex.c
int				ft_p_hex_may(int nb);
int				ft_p_hex_min(int nb);

// ft_add_str.c
void			ft_add_str(char *str, char c);

// ft_bzero.c
void			ft_bzero(void *s, size_t n);

// ft_num_size.c
unsigned int	ft_number_size(unsigned long long nb);

// ft_strjoin.c
char			*ft_strjoin(char const *s1, char const *s2);

// ft_strlen.c
int				ft_strlen(const char *str);

#endif