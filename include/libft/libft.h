/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 16:14:45 by plinscho          #+#    #+#             */
/*   Updated: 2023/11/20 21:23:22 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <ctype.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdarg.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

int		ft_isalpha(int c); // ok
int		ft_isdigit(int c); // ok
int		ft_isalnum(int c); // ok
int		ft_isascii(int c); // ok
int		ft_isprint(int c); // ok
size_t	ft_strlen(const char *s); //ok
int		ft_tolower(int c); // ok
int		ft_toupper(int c); // ok
int		ft_atoi(const char *str);

int		ft_strncmp(const char *s1, const char *s2, size_t n); //ok
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize); //ok
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len); //ok
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strdup(const char *s);
char	*ft_strndup(const char *s, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t members, size_t size);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memdel(void *ptr);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t len);

//	funciones bonus
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

// GET_NEXT_LINE

typedef struct s_gnl
{
	char			*str_buff;
	struct s_gnl	*next;
}t_line;

char	*get_next_line(int fd);
void	create_list(t_line **list, int fd);
void	append(t_line **list, char *buffer);
char	*get_line(t_line *list);
void	polish_list(t_line **list);
int		len_to_new_line(t_line *list);
void	copy_str(t_line *list, char *str);
int		found_new_line(t_line *list);
t_line	*find_last_node(t_line *list);
void	dealloc(t_line **list, t_line *clean_node, char *buff);

//  FT_PRINTF

typedef struct s_print
{
	va_list		arguments;
	char		specifier;
	int			total_len;

}t_print;

t_print	*ft_initialize_tab(t_print *tab);

int		ft_printf(const char *format, ...);
int		ft_iterate_format(const char *fmt, int print_len, int control, \
		t_print *tab);
int		ft_check_specifier(const char *format, t_print *tab, int position);

int		ft_print_char(t_print *tab, int control);
int		ft_print_string(t_print *tab, int control);
int		ft_print_int(t_print *tab, int control);
int		ft_print_unsigned(t_print *tab, int control);
char	*ft_utoa(unsigned int number);

int		ft_print_x(t_print *tab, const char x);
int		ft_get_ptr(t_print *tab);
int		ft_dectohex(unsigned int decimal, t_print *tab);
int		ft_dectoptr(unsigned long int decimal, t_print *tab);

int		ft_putchar(int c, t_print *tab);
int		ft_putstr(char *string, t_print *tab);
int		ft_count_digits(unsigned int number);

#endif
