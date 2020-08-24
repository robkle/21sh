# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rklein <rklein@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/22 16:24:22 by rklein            #+#    #+#              #
#    Updated: 2020/08/21 12:50:18 by rklein           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
ft_isdigit.c ft_isprint.c ft_itoa.c ft_memalloc.c ft_memccpy.c ft_memchr.c \
ft_memcmp.c ft_memcpy.c ft_memdel.c ft_memmove.c ft_memset.c ft_putchar.c \
ft_putchar_fd.c ft_putendl.c ft_putendl_fd.c ft_putnbr.c ft_putnbr_fd.c \
ft_putstr.c ft_putstr_fd.c ft_strcat.c ft_strchr.c ft_strclr.c ft_strcmp.c \
ft_strcpy.c ft_strdel.c ft_strdup.c ft_strequ.c ft_striter.c ft_striteri.c \
ft_strjoin.c ft_strlcat.c ft_strlen.c ft_strmap.c ft_strmapi.c ft_strncat.c \
ft_strncmp.c ft_strncpy.c ft_strnequ.c ft_strnew.c ft_strnstr.c ft_strrchr.c \
ft_strsplit.c ft_strstr.c ft_strsub.c ft_strtrim.c ft_tolower.c ft_toupper.c \
ft_lstnew.c ft_lstadd.c ft_lstiter.c ft_lstdelone.c get_next_line.c \
ft_printf.c ft_misc.c ft_base_print.c ft_char_print.c ft_double_print.c \
ft_e_print.c ft_g_print.c ft_id_memory.c ft_int_print.c ft_uint_print.c \
ft_double_flags.c ft_int_flags.c ft_uint_flags.c

OBJECTS = $(SRCS:.c=.o) 

HEADER = ./

FLAGS = -Wall -Wextra -Werror -c

all: $(NAME)
$(NAME):
	@echo Compiling libft library ...
	@gcc  $(FLAGS) $(SRCS) -I $(HEADER)
	@ar rc $(NAME) $(OBJECTS)
	@ranlib $(NAME)

clean:
	@echo Deleting libft object files ...
	@rm -f $(OBJECTS)

fclean: clean
	@echo Deleting libft library ...
	@rm -f $(NAME)

re: fclean all
