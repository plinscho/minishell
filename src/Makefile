NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I./include
LDFLAGS = -lreadline

SRC = main.c
OBJ = $(SRC:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: Makefile $(NAME) 

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $^ -o $(NAME) $(LDFLAGS)
	@printf "Compiled $(NAME) succesfully!\n"

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re