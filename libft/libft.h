/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rklein <rklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 09:06:41 by rklein            #+#    #+#             */
/*   Updated: 2020/09/10 11:51:04 by rklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stdint.h>
# include <inttypes.h>
# include <stdbool.h>
# include <limits.h>
# include <stdio.h>

# define BUFF_SIZE 8
# define FD_MAX 1024

# define BLACK			"\033[30m"
# define RED 			"\033[31m"
# define GREEN 			"\033[32m"
# define YELLOW 		"\033[33m"
# define BLUE 			"\033[34m"
# define MAGENTA 		"\033[35m"
# define CYAN 			"\033[36m"
# define WHITE			"\033[37m"
# define EOC 			"\033[0m"

typedef	struct	s_var
{
	char	sign;
	char	*flags;
	char	*fld_min;
	_Bool	dot;
	char	*prec;
	char	*type_spec;
	char	type;
	int		count;
}				t_var;

typedef struct	s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;

int				ft_atoi(const char *str);
void			ft_bzero(void *s, size_t n);
int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isascii(int c);
int				ft_isdigit(int c);
int				ft_isprint(int c);
int				ft_isspace(int c);
char			*ft_itoa(int n);
void			*ft_memalloc(size_t size);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			ft_memdel(void **ap);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memset(void *b, int c, size_t len);
void			ft_putchar(char c);
void			ft_putchar_fd(char c, int fd);
void			ft_putendl(char const *s);
void			ft_putendl_fd(char const *s, int fd);
void			ft_putnbr(int n);
void			ft_putnbr_fd(int n, int fd);
void			ft_putstr(char const *s);
void			ft_putstr_fd(char const *s, int fd);
char			*ft_strcat(char *s1, const char *s2);
char			*ft_strchr(const char *s, int c);
void			ft_strclr(char *s);
int				ft_strcmp(const char *s1, const char *s2);
char			*ft_strcpy(char *dst, const char *src);
void			ft_strdel(char **as);
char			*ft_strdup(const char *src);
int				ft_strequ(char const *s1, char const *s2);
void			ft_striter(char *s, void (*f)(char*));
void			ft_striteri(char *s, void (*f)(unsigned int, char*));
char			*ft_strjoin(char const *s1, char const *s2);
size_t			ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t			ft_strlen(const char *str);
char			*ft_strmap(char const *s, char (*f)(char));
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char			*ft_strncat(char *s1, const char *s2, size_t n);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strncpy(char *dst, const char *src, size_t len);
int				ft_strnequ(char const *s1, char const *s2, size_t n);
char			*ft_strnew(size_t size);
char			*ft_strnstr(const char *haystack, const char *needle,
		size_t len);
char			*ft_strrchr(const char *s, int c);
char			**ft_strsplit(char const *s, char c);
char			*ft_strstr(const char *haystack, const char *needle);
char			*ft_strsub(char const *s, unsigned int start, size_t len);
char			*ft_strtrim(char const *s);
int				ft_tolower(int c);
int				ft_toupper(int c);
t_list			*ft_lstnew(void const *content, size_t content_size);
void			ft_lstadd(t_list **alst, t_list *nlst);
void			ft_lstdelone(t_list **alst, void (*del)(void*, size_t));
void			ft_lstiter(t_list *lst, void (*f)(t_list *elem));
int 			get_next_line(const int fd, char **line);

/*
** ft_printf prototypes
*/

int				ft_printf(const char *format, ...);
void			ft_double_print(t_var *id, va_list args);
char			*ft_ftoa(t_var *id, long double fl, int pr);
long double		ft_prep(t_var *id, long double fl, int pr);
void			ft_int_print(t_var *id, va_list args);
char			*ft_addsign(t_var *id, char *str);
char			*ft_s_itoa(t_var *id, intmax_t n);
void			ft_uint_print(t_var *id, va_list args);
char			*ft_spad_uint(t_var *id, char *str);
void			ft_base_print(t_var *id, va_list args);
char			*ft_base(uintmax_t value, t_var *id);
char			*ft_itoa_base(uintmax_t value, int base);
void			ft_addr_print(t_var *id, va_list args);
char			*ft_zpad_uint(t_var *id, int size);
void			ft_char_print(t_var *id, va_list args);
int				ft_strchr_int(char *s, int c);
char			*ft_double_flags(t_var *id, char *str);
char			*ft_int_flags(t_var *id, char *str);
char			*ft_strmake(char c, int size);
char			*ft_spacepad(t_var *id, char *str);
char			*ft_uint_flags(t_var *id, char *str);
void			ft_e_print(t_var *id, va_list args);
char			*ft_enum(t_var *id, long double f);
char			*ft_suffix(char type, char sign, int e);
void			ft_g_print(t_var *id, va_list args);
char			*ft_cut_zero(char *str);
t_var			*ft_idalloc(void);
void			ft_reset(t_var *id);
void			ft_free_str(char **str, int s);
int				ft_free_id(t_var *id);
int				ft_is_flag(char c);
int				ft_atoi(const char *str);
int				ft_isdigit(int c);

#endif
