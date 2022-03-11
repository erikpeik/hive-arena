CC=gcc
CFLAGS=-Wall -Wextra -O3 -flto
CPPFLAGS=-I../src
LDFLAGS=-flto -L../bin -lagent

OBJS=main.o
NAME=agent

all: $(NAME)

$(NAME): $(OBJS)
	rm -f map_log
	touch map_log
	@make -C libft/
	$(CC) -o $(NAME) $(OBJS) $(LDFLAGS) -Llibft/ -lft -I includes

clean:
	@make clean -C libft/
	rm -f $(OBJS)

fclean: clean
	@make fclean -C libft/
	rm -f $(NAME)

re: fclean all
