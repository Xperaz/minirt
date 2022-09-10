NAME=miniRT
CSRCS= main.c get_next_line.c allocation.c tools.c parse_element.c parse.c split.c  vector.c  Garbage_Collector.c intersection.c mlx_func.c camera.c color.c
CFLAGS= -Wall -Wextra -Werror
CC= gcc

OBJS=$(CSRCS:.c=.o)

all: $(NAME) clean

$(NAME):$(OBJS)
	@$(CC) -lmlx -framework OpenGL -framework AppKit $(CFLAGS) $(OBJS) -o $(NAME)

%.o:%.c
	@$(CC) $(CFLAGS) -c $^

clean :
	@rm -rf $(OBJS)

fclean : clean
	@rm -rf $(NAME)


re : fclean all clean