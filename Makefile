NAME=agent
PLAYER=epk_final

all: $(NAME)

$(NAME):
	make -C src
	make -C $(PLAYER)
	cp $(PLAYER)/agent .

clean:
	make clean -C src
	make clean -C $(PLAYER)

fclean:
	make fclean -C src
	make fclean -C $(PLAYER)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
