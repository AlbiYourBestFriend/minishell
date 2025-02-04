NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
OTHER_FLAGS = -lreadline -lncurses

<<<<<<< HEAD
VPATH = sources:sources/list_handler:sources/utils:sources/parsing
=======
SOURCES = main.c \
	parsing.c \
	list_handler/command_lst.c \
	list_handler/token_lst.c \
	utils/array_len.c \
	utils/ft_copy_tab.c \
	utils/ft_free_tab.c \
>>>>>>> main

SOURCES = main.c parsing.c \
		command_lst.c token_lst.c \
		utils1.c

OBJECTS_DIR	= objects
<<<<<<< HEAD
OBJECTS		= $(addprefix $(OBJECTS_DIR)/,$(SOURCES:.c=.o))
=======
MY_OBJECTS	= $(addprefix $(OBJECTS_DIR)/, $(SOURCES:.c=.o))
>>>>>>> main

LIBFT_DIR = libft
LIBFT_A = ${LIBFT_DIR}/libft.a

all: ${NAME}

${NAME}: ${OBJECTS}
	@${MAKE} --no-print-directory -C ${LIBFT_DIR}
<<<<<<< HEAD
	${CC} ${CFLAGS} ${OTHER_FLAGS} -o ${NAME} ${OBJECTS} ${LIBFT_A}
=======
	${CC} ${CFLAGS} ${OTHER_FLAGS} ${MY_OBJECTS} ${LIBFT_A} -o ${NAME}
>>>>>>> main

$(OBJECTS_DIR)/%.o: %.c
	@mkdir -p $(OBJECTS_DIR)
	${CC} ${CFLAGS} -c $< -o $@

clean:
	@rm -rf $(OBJECTS_DIR)
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) clean
	
fclean: clean
	@rm -f $(NAME)
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re