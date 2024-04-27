# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mac <mac@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/04 19:10:12 by mcatalan@st       #+#    #+#              #
#    Updated: 2024/04/27 19:17:22 by mac              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#
# LIBFT_D = libft/
# LIBFT = libft.a

# NSERVER = minishell

# SRCS =	src/minishell.c  	\
# 		src/get_info.c   	\
# 		src/input.c		 	\
# 		src/initialize.c 	\
# 		src/colors.c 	 	\
# 		src/enviroment.c  	\
# 		src/func_ptr/func_ptr.c  	\
# 		src/func_ptr/func_ptr2.c  	\
# 		src/func_ptr/func_ptr3.c  	\
# 		src/func_ptr/func_ptr4.c  	\
# 		src/func_ptr/func_selector.c  	\
# 		src/pipes.c			\
# 		src/signals.c

# OBJS = $(SRCS:.c=.o)

# INCLUDE = -I./
# RM = rm -f
# CFLAGS = ## -Wall -Wextra -Werror

# all: makelibft $(NSERVER)

# makelibft:
# 	@make --no-print-directory -C $(LIBFT_D)

# %.o: %.c
# 	${CC} ${CFLAGS} $(INCLUDE) -c $< -o $@ 

# $(NSERVER): $(OBJS) $(LIBFT_D)$(LIBFT)
# 	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LIBFT_D)$(LIBFT) -g -lreadline -L/usr/lib/x86_64-linux-gnu

# clean:
# 	@make clean --no-print-directory -C $(LIBFT_D)
# 	$(RM) $(OBJS)

# fclean: clean
# 	$(RM) $(NSERVER)

# re: fclean all

# .PHONY: all clean fclean re makelibft


# MACOS
# Print MINISHELL and authors' names
MINISHELL_MSG = MINISHELL
AUTHORS_MSG = by oseivane el "calamidades" & ...buscando compi
MESSAGE_LEN = $$(($(shell echo $(MINISHELL_MSG) | wc -c) - 1))

PRINT_MINISHELL = @printf "$(VIOLET)%*s$(RESET)\n" $(MESSAGE_LEN) $(MINISHELL_MSG)
PRINT_AUTHORS = @echo "$(BLUE)$(AUTHORS_MSG)$(RESET)"

# Colors
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
VIOLET = \033[0;35m
RESET = \033[0m

LIBFT_D = libft/
LIBFT = libft.a

READLINE_D = readline/
READLINE_A = $(READLINE_D)libhistory.a $(READLINE_D)libreadline.a
READLINE_FLAGS = -lreadline -ltermcap
READLINE_URL = http://git.savannah.gnu.org/cgit/readline.git/snapshot/readline-bfe9c573a9e376323929c80b2b71c59727fab0cc.tar.gz
READLINE_TAR = readline.tar.gz
DEFS = -DREADLINE_LIBRARY

NAME = minishell

SRCS =	$(wildcard src/*.c)	\
		$(wildcard src/func_ptr/*.c)

OBJS = $(SRCS:.c=.o)

DEPS = $(SRCS:.c=.d)

INCLUDE = -I./
RM = rm -rf
CFLAGS = #-Wall -Wextra -Werror
OFLAGS = -g  #-fsanitize=address -fsanitize=leak

all: print_message $(READLINE_A) libft $(NAME)
	@echo "$(GREEN)Build finished successfully!$(RESET)✅"

$(READLINE_D):
			@curl -k $(READLINE_URL) > $(READLINE_TAR)
			@tar -xf $(READLINE_TAR) && mv readline-* readline
			@rm -rf $(READLINE_TAR)

$(READLINE_A): $(READLINE_D)
			@if [ ! -f $(READLINE_D)config.status ] ; then \
				printf "$(YELLOW)Configuring READLINE...$(DEFAULT)" && \
				cd ./$(READLINE_D) && \
				./configure &> /dev/null && \
				echo ✅; \
			fi
			@printf "$(YELLOW)Making READLINE...$(DEFAULT)"
			@cd ./$(READLINE_D) && make &> /dev/null
			@echo ✅

libft:
	@echo "$(YELLOW)Building libft...$(RESET)"
	@make --no-print-directory -C $(LIBFT_D)

print_message:
	$(PRINT_MINISHELL)
	$(PRINT_AUTHORS)

%.o: %.c
#   @echo "$(YELLOW)Compiling...$(RESET)"
	@${CC} ${CFLAGS} $(DEFS) -MMD $(INCLUDE) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT_D)$(LIBFT) $(READLINE_A)
	@echo "$(YELLOW)Linking...$(RESET)"
	@$(CC) $(CFLAGS) $(DEFS) $(READLINE_FLAGS) $(OBJS) -o $@ $(LIBFT_D)$(LIBFT) $(READLINE_A) $(OFLAGS)
	@echo "$(GREEN)Linked!$(RESET)✅"
-include $(DEPS)

clean:
	@make clean --no-print-directory -C $(LIBFT_D)
	@$(RM) $(OBJS) $(DEPS)
	@echo "$(RED)Cleaned minishell!$(RESET)✅"

fclean:
	@make fclean --no-print-directory -C $(LIBFT_D)
	@$(RM) $(NAME) $(DEPS) $(OBJS) $(READLINE_A)
	@echo "$(RED)Fcleaned minishell!$(RESET)✅"

jesusg:
	@echo "$(VIOLET)Jesus is watching you...$(RESET)👀"
	@$(RM) -r $(OBJS_DIR) $(OBJS) $(DEPS)
	@echo "$(RED)Jesus has cleaned your soul!$(RESET)✅"

re: fclean all

.PHONY: all clean fclean re libft readline jesusg config