NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror

SOURCES = minishell.c

SOURCES_DIR	= sources
MY_SOURCES	= $(addprefix $(SOURCES_DIR)/,$(SOURCES))
MY_OBJECTS	= $(MY_SOURCES:.c=.o)

LIFT_DIR = libft
LIBFT_A = ${LIFT_DIR}/libft.a

all: ${NAME}

${NAME}: ${MY_OBJECTS}
	${MAKE} -C ${LIFT_DIR}
	${CC} ${CFLAGS} -o ${NAME} ${MY_OBJECTS} ${LIBFT_A}

clean:
	@rm -f $(MY_OBJECTS)
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) clean
	
fclean: clean
	@rm -f $(NAME)
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
