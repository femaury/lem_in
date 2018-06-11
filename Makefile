# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: femaury <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/18 20:03:09 by femaury           #+#    #+#              #
#    Updated: 2018/06/11 15:03:12 by femaury          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in
SRC_PATH = srcs
SRC_NAME = lem_in.c lem_in_parsing.c lem_in_listfuncs.c lem_in_findbest.c \
		   lem_in_exit.c
OBJ_PATH = objs
OBJ_NAME = $(SRC_NAME:.c=.o)
SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))
CC = gcc
CFLAGS = -g -Wall -Wextra -Werror

.PHONY: all, clean, fclean, re

all:
	@$(MAKE) -C libs/libft/
	@$(MAKE) -C libs/printf/
	@$(MAKE) $(NAME)

$(NAME): $(OBJ) libs/libft/libft.a libs/printf/libftprintf.a
	@$(CC) $(CFLAGS) -Iincs -o $(NAME) $(OBJ) libs/libft/libft.a libs/printf/libftprintf.a
	@echo "\n[\033[32mOK\033[0m] $(NAME) compiled successfully."

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@$(CC) $(CFLAGS) -Iincs -o $@ -c $<
	@echo "[\033[32mOK\033[0m] $@ compiled successfully."

clean:
ifeq ($(MAKECMDGOALS), clean)
	@$(RM) $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || true
	@$(MAKE) -C libs/libft/ clean
	@$(MAKE) -C libs/printf/ clean
	@echo "\n[\033[32mOK\033[0m] $(NAME) objects cleaned.\n"
else
	@$(RM) $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || true
	@echo "\n[\033[32mOK\033[0m] $(NAME) objects cleaned.\n"
endif

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C libs/libft/ fclean
	@$(MAKE) -C libs/printf/ fclean
	@echo "\n[\033[32mOK\033[0m] $(NAME) \033[31mhas been removed.\033[0m\n"

re: fclean all
