# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/06 17:34:16 by nzhuzhle          #+#    #+#              #
#    Updated: 2023/11/08 22:47:04 by plinscho         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CC = cc
FLAGS = -Wall -Wextra -Werror -MMD -I ./

SRC = pipex.c aux.c errors.c parsing.c
OBJ = $(SRC:.c=.o)
DEPS = $(SRC:.c=.d)

SRC_BONUS = pipex_bonus.c aux_bonus.c errors_bonus.c parsing_bonus.c \
			initialize_bonus.c
OBJ_BONUS = $(SRC_BONUS:.c=.o)
DEPS_BONUS = $(SRC_BONUS:.c=.d)

SRC_LIBFT = libft.a

%.o: %.c Makefile
	$(CC) $(FLAGS) -c $< -o $@

all: make_lib $(NAME)

make_lib: 
	$(MAKE_LIBFT)

-include $(DEPS)
$(NAME): $(OBJ) $(SRC_LIBFT)
	$(CC) $(FLAGS) $(OBJ) $(SRC_LIBFT) -o $(NAME)

bonus:  make_lib .bonusp

-include $(DEPS_BONUS)
.bonusp: $(OBJ_BONUS) $(SRC_LIBFT)
	$(CC) $(FLAGS) $(OBJ_BONUS) $(SRC_LIBFT) -o $(NAME)
	@touch .bonusp

clean:
	rm -f $(OBJ) $(DEPS) $(OBJ_BONUS) $(DEPS_BONUS)

fclean: clean
	rm -f $(NAME) 
	rm -f .bonusp

re: fclean all

.PHONY: all clean fclean re