NAME = minishell
HEADER = include/minishell.h
CC = clang
CFLAGS = -Wall -Wextra -Werror -MMD -I include/

LIBFT = include/libft/libft.a
RDL = -L${HOME}/.brew/opt/readline/lib -lreadline -lhistory -ltermcap
LIBS = -L$(LIBFT) $(RDL)
MAKE_LIBFT = make -C include/libft --no-print-directory

MAIN = src/main/main

PARSER = src/parser/parser_main \
			src/parser/parser_utils \
			src/parser/initialize_sh \


LEXER = src/lexer/lexer_main \
		src/lexer/lexer_utils \
		src/lexer/heredoc \
		src/lexer/heredoc_utils

EXPANSER = src/expanser/expanser
EXECUTOR = src/executor/executor
ERRORS = src/errors/errors
ENV = src/env/env src/env/env_list
BUILTINS = src/builtins/cd
SIGNALS = src/signals/signals

SRC = $(addsuffix .c, $(PARSER)) \
	  $(addsuffix .c, $(ENV)) \
	  $(addsuffix .c, $(MAIN)) \
	  $(addsuffix .c, $(BUILTINS)) \
	  $(addsuffix .c, $(LEXER)) \
	  $(addsuffix .c, $(EXPANSER)) \
	  $(addsuffix .c, $(EXECUTOR)) \
	  $(addsuffix .c, $(SIGNALS)) \
	  $(addsuffix .c, $(ERRORS)) 

#F_OBJ = obj/
OBJ = $(addprefix $(F_OBJ), $(SRC:.c=.o))
DEP = $(addprefix $(F_OBJ), $(SRC:.c=.d))

all: make_lib $(NAME)

make_lib:
	$(MAKE_LIBFT)

-include $(DEPS)
%.o: %.c Makefile
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

#vpath %.c src/main/:src/parser/:src/env/:src/builtins/:src/executor/:src/expanser/:src/lexer/:src/signals/:src/errors/

$(NAME): $(OBJ) ./$(LIBFT)
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(^) $(LIBS) -o ${NAME}
	@printf "Compiled $(NAME) succesfully!\n"

clean:
	$(MAKE_LIBFT) clean
	@rm -rf $(OBJ) $(DEP)
	@rm -rf $(F_OBJ)
	@printf "[MINIS] Removed objects.\n"

fclean: clean
	$(MAKE_LIBFT) fclean
	@rm -f $(NAME)
	@printf "[MINISH] Removed $(NAME).\n"

re: fclean all


.PHONY: all clean fclean re