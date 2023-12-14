# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vics <vics@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/04 19:10:12 by mcatalan@st       #+#    #+#              #
#    Updated: 2023/12/13 15:15:51 by vics             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT_D = libft/
LIBFT = libft.a

FT_PRINTF_D = ft_printf/
FT_PRINTF = libftprintf.a

NSERVER = minishell

SRCS =	src/minishell.c \
		src/colors.c
		

OBJS = $(SRCS:.c=.o)

INCLUDE = -I./
RM = rm -f
CFLAGS = -Wall -Wextra -Werror

all: makelibft $(NSERVER)

makelibft:
	@make --no-print-directory -C $(LIBFT_D)

makeftprintf:
	@make --no-print-directory -C $(FT_PRINTF_D)

%.o: %.c
	${CC} ${CFLAGS} $(INCLUDE) -c $< -o $@ 

$(NSERVER): $(OBJS) $(LIBFT_D)$(LIBFT) $(FT_PRINTF_D)$(FT_PRINTF)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LIBFT_D)$(LIBFT) $(FT_PRINTF_D)$(FT_PRINTF) -g -lreadline -L/usr/lib/x86_64-linux-gnu

clean:
	@make clean --no-print-directory -C $(LIBFT_D)
	@make clean --no-print-directory -C $(FT_PRINTF_D)
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NSERVER)

re: fclean all

.PHONY: all clean fclean re makelibft makeftprintf