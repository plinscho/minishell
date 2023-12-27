# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nzhuzhle <nzhuzhle@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/07 21:22:24 by nzhuzhle          #+#    #+#              #
#    Updated: 2023/12/27 22:39:30 by nzhuzhle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
HEADER = ./include/minishell.h

CC = cc
CFLAGS = -Wall -Wextra -Werror -MMD -I ./include -g -fsanitize=address

LIBFT = include/libft/libft.a
RDL = -L${HOME}/.brew/opt/readline/lib -lreadline -lhistory -ltermcap
RLINE = include/readline/libreadline.a
RLINE_PATH = include/readline/
RHIST = include/readline/libhistory.a
LIBS = -L include/libft -L $(RLINE_PATH)
MAKE_LIBFT = make -C include/libft --no-print-directory
MAKE_RLINE = make -C include/readline --no-print-directory

MAIN = src/main/main src/main/initialize_sh 

PARSER = src/parser/parser src/parser/parser_utils src/parser/printer

LEXER = src/lexer/lexer src/lexer/lexer_utils src/lexer/quotes \
		src/lexer/heredoc src/lexer/fd_utils src/lexer/check_syntax \
		src/lexer/utils \

EXPANSER = src/expanser/expanser src/expanser/expanser_utils \
src/expanser/exp_struct 
EXECUTOR = src/executor/executor src/executor/exec_utils

ERRORS = src/errors/errors 

ENV = src/env/env src/env/env_list src/env/env_free src/env/env_utils \
		src/env/env_sort

BUILTINS = src/builtins/cd src/builtins/echo src/builtins/env \
			src/builtins/exit src/builtins/export src/builtins/export_utils \
			src/builtins/pwd src/builtins/unset

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

F_OBJ = obj/
OBJ = $(patsubst src/%.c, $(F_OBJ)%.o, $(SRC))
DEP = $(addprefix $(F_OBJ), $(SRC:.c=.d))

all: make_lib $(RLINE) $(NAME)

make_lib:
	$(MAKE_LIBFT) 

$(F_OBJ)%.o: src/%.c Makefile $(HEADER)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

-include ${DEP}
$(NAME): $(OBJ) ./$(LIBFT) ./$(RLINE) ./$(RHIST)
	@$(CC) $(CFLAGS) $(^) -ltermcap -lreadline -o $(NAME)
	@printf "Compiled $(NAME) succesfully!\n"

$(RLINE):
	@cd $(RLINE_PATH) && ./configure &>/dev/null
	@$(MAKE_RLINE) 
	@printf "Compiled READLINE succesfully!\n"

clean:
	$(MAKE_LIBFT) clean
	@rm -rf $(F_OBJ)
	@printf "[MINIS] Removed objects.\n"

fclean: clean
	$(MAKE_LIBFT) fclean
	@rm -f $(NAME)
	@printf "[MINISH] Removed $(NAME).\n"

cleanrl:
	@make -s -C include/readline mostlyclean
	@echo "READLINE removed.\n"

gitstat:
	git log --graph --oneline --all --decorate


re: fclean all

.PHONY: all clean fclean re make_lib cleanrl
