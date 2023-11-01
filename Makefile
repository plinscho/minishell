NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror

LDFLAGS = -lreadline
LIB_PATH = include/libft
MINI_H = include/minishell.h
LIBFT_H = $(LIB_PATH)/libft.a

#BUILTINS
#LEXER
#PARSER
#EXECUTOR
#EXPANSER

ENV = enl_lst env 




SRC = src/main.c \
		src/input/input.c \
		src/signals/signals.c 

OBJ = $(SRC:c=o)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@printf "Compiling ...$<\n"
	@mkdir -p $(@D)

-include $(DEPS)

all: $(LIBFT_H) $(NAME) Makefile

$(LIBFT_H):
	@printf "Checking libft Now :D\n"
	@$(MAKE) -sC $(LIB_PATH)

$(NAME): $(MINI_H) $(LIBFT_H) $(OBJ)
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -o ${NAME} $(OBJ) -I$(LIB_PATH) -L$(LIB_PATH) \
	-lft $(LDFLAGS)
	@printf "Compiled $(NAME) succesfully!\n"

clean:
	@$(MAKE) -sC $(LIB_PATH) clean
	@rm -rf $(OBJDIR)
	@printf "[MINIS] Removed objects.\n"

fclean: clean
	@$(MAKE) -sC $(LIB_PATH) fclean
	@rm -f $(NAME)
	@printf "[MINISH] Removed $(NAME).\n"

re: fclean all


.PHONY: all clean fclean re
