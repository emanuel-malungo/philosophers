CC = cc
SRCDIR = ./src
INCDIR = ./include
NAME = philo
CFLAGS = -Wall -Wextra -Werror -I$(INCDIR)

SRCS = $(SRCDIR)/philo.c \
       $(SRCDIR)/utils.c \
       $(SRCDIR)/fork.c \
       $(SRCDIR)/threads.c \
       $(SRCDIR)/routine.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
