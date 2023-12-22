# Nombre del archivo creado
NAME = libft.a

# Compilar ficheros

CC = gcc
FLAGS = -Wall -Werror -Wextra
AR = ar rc
LIB = libft.h

# Funciones auxiliares (sources)

SOURCES_DIR = bools fd strings memory lists gnl ft_printf

#sources for each directory
BOOLS_SRC = ft_isalpha.c ft_isalnum.c ft_isdigit.c ft_isascii.c \
			ft_isprint.c ft_isspace.c

STRINGS_SRC = ft_strlen.c ft_strlcpy.c ft_toupper.c ft_tolower.c ft_strncmp.c \
			ft_strnstr.c ft_atoi.c ft_strdup.c ft_atoi.c ft_strchr.c ft_strrchr.c \
			ft_strlcat.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
			ft_striteri.c ft_strmapi.c ft_strndup.c ft_strisnum.c ft_strcmp.c \
			ft_strdup_free.c

MEMORY_SRC = ft_bzero.c ft_calloc.c ft_memcpy.c ft_memcpy.c ft_memchr.c \
			ft_memcmp.c ft_memset.c ft_memmove.c ft_memdel.c

FD_SRC = ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c

LISTS_SRC = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
			ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

GNL_SRC = get_next_line.c get_next_line_utils.c 

FT_PRINTF_SRC = ft_print_char.c ft_print_hex.c ft_print_int.c ft_print_ptr.c ft_print_string.c \
				ft_print_unsigned.c ft_printf.c ft_utils.c

SOURCES =	$(addprefix bools/, $(BOOLS_SRC)) \
			$(addprefix strings/, $(STRINGS_SRC)) \
			$(addprefix memory/, $(MEMORY_SRC)) \
			$(addprefix fd/, $(FD_SRC)) \
			$(addprefix lists/, $(LISTS_SRC)) \
			$(addprefix gnl/, $(GNL_SRC)) \
			$(addprefix ft_printf/, $(FT_PRINTF_SRC))

OBJECTS = $(SOURCES:.c=.o)
DEPS = $(SOURCES:.c=.d)

all: $(NAME)

%.o: %.c Makefile $(LIB)
	@printf "Compiling ... $<\n"
	@$(CC) -MMD -c $(FLAGS) $< -o $@

$(NAME): $(OBJECTS) $(LIB)
	@echo "\nLinking ... $@\n"
	@$(AR) ${NAME} ${OBJECTS}
	@echo "Done!"

clean: 
	@rm -f $(OBJECTS) $(DEPS)
	@printf "[LIBFT] Removed Objects and dependencies.\n"

fclean:
	@rm -f $(OBJECTS) $(DEPS)
	@rm -f $(NAME)
	@printf "[LIBFT] Removed $(NAME) and dependencies.\n"

re:	fclean all

-include $(DEPS)

.PHONY: all clean fclean re