# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mac <mac@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/04 19:10:12 by mcatalan@st       #+#    #+#              #
#    Updated: 2024/04/27 19:16:36 by mac              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

BONUS = .bonus

CFLAGS = -Wall -Wextra -Werror

SRCS = 	ft_isalpha.c		\
		ft_isdigit.c		\
		ft_isalnum.c		\
		ft_isascii.c		\
		ft_isprint.c		\
		ft_strlen.c			\
		ft_strlcpy.c		\
		ft_atoi.c			\
		ft_toupper.c		\
		ft_memset.c			\
		ft_bzero.c			\
		ft_memcpy.c			\
		ft_memmove.c		\
		ft_strlcat.c		\
		ft_tolower.c		\
		ft_strchr.c			\
		ft_strrchr.c		\
		ft_memchr.c			\
		ft_memcmp.c			\
		ft_strncmp.c		\
		ft_strcmp.c			\
		ft_strnstr.c		\
		ft_calloc.c			\
		ft_strdup.c			\
		ft_substr.c			\
		ft_strjoin.c		\
		ft_strtrim.c		\
		ft_split.c			\
		ft_itoa.c			\
		ft_add_str.c		\
		ft_num_size.c		\
		ft_strmapi.c		\
		ft_striteri.c		\
		ft_putchar_fd.c		\
		ft_putchar.c		\
		ft_putstr_fd.c		\
		ft_putendl_fd.c		\
		ft_putnbr_fd.c		\
		ft_lstnew.c 		\
		ft_lstadd_front.c 	\
		ft_lstsize.c		\
		ft_lstlast.c 		\
		ft_lstadd_back.c 	\
		ft_lstdelone.c 		\
		ft_lstclear.c 		\
		ft_lstiter.c 		\
		ft_lstmap.c 		\
		ft_atol.c			\


SRCSB = ft_lstnew.c 		\
		ft_lstadd_front.c	\
		ft_lstsize.c		\
		ft_lstlast.c		\
		ft_lstadd_back.c	\
		ft_lstdelone.c		\
		ft_lstclear.c		\
		ft_lstiter.c		\
		ft_lstmap.c			\

OBJS = $(SRCS:.c=.o)

OBJSBONUS = $(SRCSB:.c=.o)

INCLUDE = -I ./

RM = rm -f

DEPS = $(SRCS:.c=.d)

DEPS_BONUS = $(SRCSB:.c=.d)

%.o: %.c libft.h
	@${CC} ${CFLAGS} -MMD $(INCLUDE) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)

	ar -rcs $(NAME) $(OBJS)

-include $(DEPS)

bonus: $(BONUS)

$(BONUS) : $(OBJS) $(OBJSBONUS)

	ar -rcs $(NAME) $(OBJS) $(OBJSBONUS)

-include $(DEPS_BONUS)

clean:
	$(RM) $(OBJS) $(OBJSBONUS) $(DEPS) $(DEPS_BONUS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
.PHONY: all bonus clean fclean re
