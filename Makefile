NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
OTHER_FLAGS = -lreadline -lncurses

SOURCES	=	command_lst.c \
			token_lst.c \
			check_quotes.c \
			handle_env_var_utils_2.c \
			handle_env_var_utils.c \
			handle_env_var.c \
			parsing.c \
			copy_tab.c \
			free_tab.c \
			clean_cmd.c \
			init_data.c \
			print_error.c \
			split_cmd_line_utils.c \
			split_cmd_line.c \
			tab_len.c \
			main.c \
			redirection_handler.c \
			open_files.c

VPATH = sources:sources/list_handler:sources/utils:sources/parsing:sources/execute

SOURCES_DIR	= sources
MY_SOURCES	= $(addprefix $(SOURCES_DIR)/,$(SOURCES))

OBJECTS_DIR	= objects
OBJECTS		= $(addprefix $(OBJECTS_DIR)/,$(SOURCES:.c=.o))

LIBFT_DIR = libft
LIBFT_A = ${LIBFT_DIR}/libft.a

all: ${NAME}

${NAME}: ${OBJECTS}
	@${MAKE} --no-print-directory -C ${LIBFT_DIR}
	${CC} ${CFLAGS} ${OTHER_FLAGS} -o ${NAME} ${OBJECTS} ${LIBFT_A}

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