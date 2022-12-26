SRCS	=	fract-ol.c \
			math_shit.c \
			graphic_shit.c

NAME	=	./fractol

OBJS	= 	${SRCS:.c=.o}

BONUS_OBJS	= ${BONUS:.c=.o}

CC	= 	gcc


CFLAGS	= 	-Wall -Wextra -Werror


.c.o:

		${CC} -Imlx -c $< -o ${<:.c=.o}



all:	${OBJS}
	$(CC) $(OBJS) -I /usr/X11/include -g -L /usr/X11/lib -l mlx -framework OpenGL -framework AppKit -o $(NAME)


clean:
		rm -f ${OBJS}


fclean:	clean
		rm -f ${NAME}


re:	fclean all

.PHONY : 	all clean fclean re
