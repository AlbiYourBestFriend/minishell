NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
OTHER_FLAGS = -lreadline -lncurses

SOURCES = main.c \
	parsing.c \
	list_handler/command_lst.c \
	list_handler/token_lst.c \
	utils/array_len.c \
	utils/ft_clean_cmd.c \
	utils/ft_copy_tab.c \
	utils/ft_free_tab.c \

SOURCES_DIR	= sources
MY_SOURCES	= $(addprefix $(SOURCES_DIR)/,$(SOURCES))

OBJECTS_DIR	= objects
MY_OBJECTS	= $(addprefix $(OBJECTS_DIR)/, $(SOURCES:.c=.o))

LIBFT_DIR = libft
LIBFT_A = ${LIBFT_DIR}/libft.a

all: ${NAME}

${NAME}: ${MY_OBJECTS}
	@${MAKE} --no-print-directory -C ${LIBFT_DIR}
	${CC} ${CFLAGS} ${OTHER_FLAGS} ${MY_OBJECTS} ${LIBFT_A} -o ${NAME}

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
