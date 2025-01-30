NAME = minishell

SOURCES = src/minishell.c

OBJECTS = ${SOURCES:.c=.o}

LIFT_DIR = libft
LIBFT_A = ${LIFT_DIR}/libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror

all: ${NAME}

${NAME}: ${OBJECTS}
	${MAKE} -C ${LIFT_DIR} bonus
	${CC} ${CFLAGS} ${OBJECTS} -o ${NAME}

clean:
	${MAKE} -C ${LIFT_DIR} clean
	rm -f src/*.o
	rm -f *.o

fclean: clean
	${MAKE} -C ${LIFT_DIR} fclean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re
