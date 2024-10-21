CC = cc
DIR_SRC = ./src
NAME = philosopher
DIR_INC = ./include
CFLAGS = -Wall -Wextra -Werror -I $(DIR_INC)

SRC = $(DIR_SRC)/philosopher.c \
      $(DIR_SRC)/utils.c 

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
