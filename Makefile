# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vics <vics@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/04 19:10:12 by mcatalan@st       #+#    #+#              #
#    Updated: 2024/01/17 15:30:25 by vics             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT_D = libft/
LIBFT = libft.a

NSERVER = minishell

SRCS =	src/minishell.c  \
		src/get_info.c   \
		src/input.c		 \
		src/initialize.c \
		src/colors.c \
		src/signals.c

OBJS = $(SRCS:.c=.o)

INCLUDE = -I./
RM = rm -f
CFLAGS = ## -Wall -Wextra -Werror

all: makelibft $(NSERVER)

makelibft:
	@make --no-print-directory -C $(LIBFT_D)

%.o: %.c
	${CC} ${CFLAGS} $(INCLUDE) -c $< -o $@ 

$(NSERVER): $(OBJS) $(LIBFT_D)$(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LIBFT_D)$(LIBFT) -g -lreadline -L/usr/lib/x86_64-linux-gnu

clean:
	@make clean --no-print-directory -C $(LIBFT_D)
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NSERVER)

re: fclean all

.PHONY: all clean fclean re makelibft