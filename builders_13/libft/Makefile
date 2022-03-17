# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emende <emende@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/29 15:19:20 by emende            #+#    #+#              #
#    Updated: 2022/03/15 15:21:21 by emende           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c

OBJS = ft_putchar_fd.o ft_putendl_fd.o ft_putnbr_fd.o ft_putstr_fd.o

CFLAG = -Wall -Wextra -Werror

RED = \033[0;31m
LGRAY = \033[1;30m
LGREEN = \033[1;32m
WHITE = \033[1;37m

all: $(NAME)

$(NAME):
#	@echo "$(LGRAY)[LIBFT] $(LGREEN)Making objects..."
	@gcc $(CFLAG) -c $(SRCS)
#	@echo "$(LGRAY)[LIBFT] $(LGREEN)Crating library from object files..."
	@ar rcs $(NAME) $(OBJS)
	@echo "$(LGRAY)[LIBFT] $(LGREEN)Libft compiled..."

clean:
	@echo "$(LGRAY)[LIBFT] $(RED)Cleaning object files..."
	@/bin/rm -f $(OBJS)

fclean: clean
	@echo "$(LGRAY)[LIBFT] $(RED)Removing libft.a library file..."
	@/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
