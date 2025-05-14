CC = cc

CFLAGS = -Wall -Wextra -Werror

SRC =	philo.c			\
		parsing.c		\
		leaks.c			\
		init.c			\
		routine.c	\
		print.c			\
		monitor.c	\
		actions.c		\
		time.c		\

OBJ = $(SRC:.c=.o)

NAME = philo

HDR = philo.h

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

%.o: %.c $(HDR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean
