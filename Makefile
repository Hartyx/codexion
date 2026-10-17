NAME = codexion
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -Iinclude
SRC = src/main.c src/parsing.c src/time_utils.c src/init.c src/cleanup.c src/log.c src/simulation.c src/coder.c src/dongle.c src/stop.c src/monitor.c

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c include/codexion.h
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
