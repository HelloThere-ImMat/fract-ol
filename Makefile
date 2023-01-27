OBJ_DIR = obj

SRCS	=	fract-ol.c \
			math_utils.c \
			graphic_utils.c \
			fract-ol_utils.c \
			str_utils.c

NAME	=	./fractol

OBJS	= 	$(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

CC	= 	gcc

CFLAGS	= 	-Wall -Wextra -Werror

all: ${NAME}

${NAME}: ${OBJS}
	${CC} ${OBJS} -I minilibx/libmxl.a -L ./minilibx -l mlx -lXext -lX11 -o $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	${CC} ${CFLAGS} -c $< -o $@

mac :	${OBJS}
	$(CC) $(OBJS) -I /usr/X11/include -g -L /usr/X11/lib -l mlx -framework OpenGL -framework AppKit -o $(NAME)


clean:
	rm -f ${OBJS} ${BONUS_OBJS}

fclean: clean
	rm -f ${NAME} ${BONUS_NAME}

re: fclean all

.PHONY: all clean fclean re
