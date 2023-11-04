NAME = minishell
<<<<<<< HEAD
CC = clang
CFLAGS = -Wall -Wextra -Werror -I include/ 
=======
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -I include/ -I include/libft/
>>>>>>> 4772314bf21fd092f3342fbc5e46abb45f02d7bd

LDFLAGS = -lreadline
LIB_PATH = include/libft
HEADER = include/minishell.h
LIBFT_H = $(LIB_PATH)/libft.a

#BUILTINS
#PARSER
#EXECUTOR
#EXPANSER

<<<<<<< HEAD
LEXER = here_doc lexer_main lexer_utils
ENV = env_lst env
=======
MAIN = main
LEXER = lexer_main lexer_utils
ENV = env env_list
>>>>>>> 4772314bf21fd092f3342fbc5e46abb45f02d7bd


SRC = $(addsuffix .c, $(addprefix src/env/, $(ENV))) \
	  $(addsuffix .c, $(addprefix src/lexer/, $(LEXER))) \
  	  $(addsuffix .c, $(addprefix src/main/, $(MAIN)))


<<<<<<< HEAD
SRC = $(addsuffix .c, $(addprefix src/env/, $(ENV))) \
	  $(addsuffix .c, $(addprefix src/lexer/, $(LEXER))) \
	  $(addsuffix .c, $(addprefix src/main/, $(MAIN))) \
	  
OBJ = $(SRC:c=o)

all: $(LIBFT_H) $(NAME) Makefile

%.o: %.c
	@printf "\033[0;33mAdding the sauce.. %-33.33s\r" $@
	@${CC} ${CFLAGS} -c $< -o $@

-include $(DEPS)

$(NAME): $(MINI_H) $(LIBFT_H) $(OBJ)
	@echo "Rolling the kebab..."
	@$(CC) $(CFLAGS) -o ${NAME} $(OBJ) $(LDFLAGS) -L libft -lft
	@printf "Compiled $(NAME) succesfully!\n"
=======
OBJ = $(SRC:c=o)

%.o: %.c
	@printf "Rolling minishell objects...\r" $@
	@${CC} ${CFLAGS} -c $< -o $@

all: $(LIBFT_H) Makefile $(NAME)
>>>>>>> 4772314bf21fd092f3342fbc5e46abb45f02d7bd

$(LIBFT_H):
	@printf "Checking libft Now :D\n"
	@$(MAKE) -sC $(LIB_PATH)

<<<<<<< HEAD
=======
$(NAME): $(HEADER) $(LIBFT_H) $(OBJ)
	@$(CC) $(CFLAGS) -o ${NAME} $(OBJ) -L include/libft -lft $(LDFLAGS)
	@printf "Compiled $(NAME) succesfully!\n"
>>>>>>> 4772314bf21fd092f3342fbc5e46abb45f02d7bd

clean:
	@$(MAKE) -sC $(LIB_PATH) clean
	@rm -rf $(OBJ)
	@printf "[MINIS] Removed objects.\n"

fclean:
	@$(MAKE) -sC $(LIB_PATH) fclean
	@rm -rf $(OBJDIR)
	@rm -f $(NAME)
	@printf "[MINISH] Removed $(NAME).\n"

re: fclean all


.PHONY: all clean fclean re
