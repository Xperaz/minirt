# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aouhadou <aouhadou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/23 10:28:09 by aouhadou          #+#    #+#              #
#    Updated: 2022/09/23 13:45:08 by aouhadou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=miniRT
CSRCS= main.c get_next_line.c allocation.c tools.c parse_element.c parse.c\
	split.c  vector.c normal_vector.c vector2.c ray_tracing.c parse_objects.c\
	Garbage_Collector.c intersection.c mlx_func.c camera.c color.c\
	surface_normale.c world.c split_utils.c
	
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