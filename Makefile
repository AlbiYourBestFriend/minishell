NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

SOURCES = main.c

SOURCES_DIR	= sources
MY_SOURCES	= $(addprefix $(SOURCES_DIR)/,$(SOURCES))

OBJECTS_DIR	= objects
MY_OBJECTS	= $(addprefix $(OBJECTS_DIR)/,$(notdir $(MY_SOURCES:.c=.o)))

LIBFT_DIR = libft
LIBFT_A = ${LIBFT_DIR}/libft.a

all: ${NAME}

${NAME}: ${MY_OBJECTS}
	@${MAKE} --no-print-directory -C ${LIBFT_DIR}
	${CC} ${CFLAGS} -o ${NAME} ${MY_OBJECTS} ${LIBFT_A}

$(OBJECTS_DIR)/%.o: $(SOURCES_DIR)/%.c
	${CC} ${CFLAGS} -c $< -o $@

clean:
	@rm -f $(MY_OBJECTS)
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) clean
	
fclean: clean
	@rm -f $(NAME)
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
