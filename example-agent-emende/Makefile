CC=gcc
CFLAGS=-Wall -Wextra -O3 -flto
CPPFLAGS=-I../src
LDFLAGS=-flto -L../bin -lagent

OBJS=main.o print_map.o initialize_and_update.o fov.o return_to_hive.o
NAME=agent

all: $(NAME)

$(NAME): $(OBJS)
	rm -f map_log
	touch map_log
	@make -C libft/
	$(CC) -o $(NAME) $(OBJS) $(LDFLAGS) -Llibft/ -lft -I libft/includes

clean:
	@make clean -C libft/
	rm -f $(OBJS)

fclean: clean
	@make fclean -C libft/
	rm -f $(NAME)

re: fclean all
