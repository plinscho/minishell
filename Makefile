NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -I include/ -I include/libft/

LDFLAGS = -lreadline
LIB_PATH = include/libft
HEADER = include/minishell.h
LIBFT_H = $(LIB_PATH)/libft.a

#BUILTINS
#PARSER
#EXECUTOR
#EXPANSER

MAIN = main
LEXER = lexer_main lexer_utils
ENV = env env_list


SRC = $(addsuffix .c, $(addprefix src/env/, $(ENV))) \
	  $(addsuffix .c, $(addprefix src/lexer/, $(LEXER))) \
  	  $(addsuffix .c, $(addprefix src/main/, $(MAIN)))


OBJ = $(SRC:c=o)

%.o: %.c
	@printf "Rolling minishell objects...\r" $@
	@${CC} ${CFLAGS} -c $< -o $@

all: $(LIBFT_H) Makefile $(NAME)

$(LIBFT_H):
	@printf "Checking libft Now :D\n"
	@$(MAKE) -sC $(LIB_PATH)

$(NAME): $(HEADER) $(LIBFT_H) $(OBJ)
	@$(CC) $(CFLAGS) -o ${NAME} $(OBJ) -L include/libft -lft $(LDFLAGS)
	@printf "Compiled $(NAME) succesfully!\n"

clean:
	@$(MAKE) -sC $(LIB_PATH) clean
	@rm -rf $(OBJ)
	@printf "[MINIS] Removed objects.\n"

fclean: clean
	@$(MAKE) -sC $(LIB_PATH) fclean
	@rm -f $(NAME)
	@printf "[MINISH] Removed $(NAME).\n"

re: fclean all


.PHONY: all clean fclean re
