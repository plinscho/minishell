NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror

LDFLAGS = -lreadline
LIB_PATH = include/libft
MINI_H = include/minishell.h
LIBFT = $(LIB_PATH)/libft.a

OBJ = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))
SRC = src/main.c \
		src/input/input.c \
		src/signals/signals.c

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@printf "Compiling ...$<\n"
	@mkdir -p $(@D)
	gcc $(CFLAGS) -c $< -o $@ -I$(LIB_PATH)

DEPS = $(SCR:.c=.d)
-include $(DEPS)

all: $(NAME) $(LIBFT)

$(LIBFT):
	@printf "Checking libft Now :D\n"
	@$(MAKE) -sC $(LIB_PATH)

$(NAME): $(MINI_H) $(LIBFT) $(OBJ)
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