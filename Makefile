CC = cc -fsanitize=thread -g
DIR_SRC = ./src
NAME = philo
DIR_INC = ./include
CFLAGS = -Wall -Wextra -Werror -I $(DIR_INC)

SRC = $(DIR_SRC)/philo.c \
      $(DIR_SRC)/utils.c \
	  $(DIR_SRC)/init.c \
	  $(DIR_SRC)/fork.c \
	  $(DIR_SRC)/threads.c \
	  $(DIR_SRC)/routine.c \

OBJ = $(SRC:$(DIR_SRC)/%.c=%.o)

all: $(NAME)

%.o: $(DIR_SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
