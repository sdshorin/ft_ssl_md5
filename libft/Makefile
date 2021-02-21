# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bjesse <bjesse@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/06 17:09:44 by bjesse            #+#    #+#              #
#    Updated: 2021/02/21 04:23:01 by bjesse           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
COMPILER = gcc
FLAGS = -g -Wall -Wextra -Werror

SOURCE = ft_bublesort.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
ft_isdigit.c ft_isprint.c ft_itoa.c ft_lstadd.c ft_lstdel.c ft_lstdelone.c \
ft_lstiter.c ft_lstmap.c ft_lstnew.c ft_memalloc.c ft_memccpy.c ft_memchr.c \
ft_memcmp.c ft_memcpy.c ft_memdel.c ft_memmove.c ft_memset.c ft_putchar.c \
ft_putchar_fd.c ft_putendl.c ft_putendl_fd.c ft_putnbr.c ft_putnbr_fd.c \
ft_putstr.c ft_putstr_fd.c ft_strcat.c ft_strchr.c ft_strclr.c ft_strcmp.c \
ft_strcpy.c ft_strdel.c ft_strdup.c ft_strequ.c ft_striter.c ft_striteri.c \
ft_strjoin.c ft_strlcat.c ft_strlen.c ft_strmap.c ft_strmapi.c ft_strncat.c \
ft_strncmp.c ft_strncpy.c ft_strnequ.c ft_strnew.c ft_strnstr.c ft_strrchr.c \
ft_strsplit.c ft_strstr.c ft_strsub.c ft_strtrim.c ft_tolower.c ft_toupper.c \
ft_atoi.c ft_alltolower.c ft_alltoup.c ft_clamp.c ft_max.c \
ft_min.c get_next_line.c ft_findchar.c ft_write_char_many.c char_vector.c \
ft_quick_sort.c ft_str_replace.c
INCLUDES = ./
HEADERS = libft.h
OBJ = $(patsubst %.c, %.o, $(SOURCE))

all: $(NAME)
	@echo > /dev/null

%.o: %.c $(HEADERS)
	@$(COMPILER) $(FLAGS) -o $@ -c $<
	@echo ".\c"

$(NAME): $(OBJ)
	@ar rc $(NAME) $(SOURCE:.c=.o)
	@ranlib $(NAME)
	@echo "$(NAME) created"


clean:
	@/bin/rm -f $(SOURCE:.c=.o)
	@echo "Libft object files deleted"

fclean: clean
	@/bin/rm -f $(NAME)
	@echo "$(NAME) deleted"

re: fclean all
