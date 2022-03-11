# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emende <emende@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/29 15:19:20 by emende            #+#    #+#              #
#    Updated: 2022/01/16 21:05:18 by emende           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS_DIR = sources/
SRCS_LIST = ft_atoi.c ft_bzero.c ft_intlen.c ft_isalnum.c ft_isalpha.c \
			ft_isascii.c ft_isdigit.c ft_isprint.c ft_isspace.c ft_itoa.c \
			ft_memalloc.c ft_memccpy.c ft_memchr.c ft_memcmp.c ft_memcpy.c \
			ft_memdel.c ft_memmove.c ft_memset.c ft_putchar.c ft_putchar_fd.c \
			ft_putendl.c ft_putendl_fd.c ft_putnbr.c ft_putnbr_fd.c \
			ft_putstr.c ft_putstr_fd.c ft_strcat.c ft_strchr.c ft_strclen.c \
			ft_strclr.c ft_strcmp.c ft_strcpy.c ft_strdel.c ft_strdup.c \
			ft_strequ.c ft_striter.c ft_striteri.c ft_strjoin.c ft_strlcat.c \
			ft_strlen.c ft_strmap.c ft_strmapi.c ft_strncat.c ft_strncmp.c \
			ft_strncpy.c ft_strnequ.c ft_strnew.c ft_strnstr.c ft_strrchr.c \
			ft_strsplit.c ft_strstr.c ft_strsub.c ft_strtrim.c ft_tolower.c \
			ft_toupper.c ft_strrev.c ft_ispunct.c ft_lstnew.c ft_lstdelone.c \
			ft_lstdel.c ft_lstadd.c ft_lstiter.c ft_lstmap.c ft_strndup.c \
			get_next_line.c

SRCS = $(addprefix $(SRCS_DIR), $(SRCS_LIST))

OBJS = $(SRCS_LIST:.c=.o)

INCL_FOLDER = includes/

INCLUDES = -I $(INCL_FOLDER)

OPTIONS = -c

CFLAG = -Wall -Wextra -Werror -Wconversion

RED = \033[0;31m
LGRAY = \033[1;30m
LGREEN = \033[1;32m
WHITE = \033[1;37m

all: $(NAME)

$(NAME):
	@echo "$(LGRAY)[LIBFT] $(LGREEN)Making objects..."
	@gcc $(CFLAG) $(INCLUDES) $(OPTIONS) $(SRCS)
	@echo "$(LGRAY)[LIBFT] $(LGREEN)Crating library from object files..."
	@ar rcs $(NAME) $(OBJS)
	@echo "$(LGRAY)[LIBFT] $(LGREEN)Generated archive libft.a"

clean:
	@echo "$(LGRAY)[LIBFT] $(RED)Cleaning object files..."
	@/bin/rm -f $(OBJS)

fclean: clean
	@echo "$(LGRAY)[LIBFT] $(RED)Removing libft.a library file..."
	@/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
