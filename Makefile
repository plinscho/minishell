NAME = minishell
CC = clang
CFLAGS = -Wall -Wextra -Werror -I include/ 

LDFLAGS = -lreadline
LIB_PATH = include/libft
MINI_H = include/minishell.h
LIBFT_H = $(LIB_PATH)/libft.a

#BUILTINS
#PARSER
#EXECUTOR
#EXPANSER

LEXER = here_doc lexer_main lexer_utils
ENV = env_lst env




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

$(LIBFT_H):
	@printf "Checking libft Now :D\n"
	@$(MAKE) -sC $(LIB_PATH)


clean:
	@$(MAKE) -sC $(LIB_PATH) clean
	@rm -rf $(OBJDIR)
	@printf "[MINIS] Removed objects.\n"

fclean:
	@$(MAKE) -sC $(LIB_PATH) fclean
	@rm -rf $(OBJDIR)
	@rm -f $(NAME)
	@printf "[MINISH] Removed $(NAME).\n"

re: fclean all


.PHONY: all clean fclean re
