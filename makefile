NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -I. -fsanitize=thread -g
RM = rm -f

SRCS =	files/main.c \
		files/utils.c \
		files/init.c \
		files/check_arg.c \
		files/program.c \
		files/actions.c \
		files/monitor.c \
		files/cleanup.c \

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

files/%.o: files/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re