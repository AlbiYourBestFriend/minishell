NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
OTHER_FLAGS = -lreadline -lncurses

SOURCES	=	ft_cd_utils.c \
			ft_cd.c \
			ft_echo.c \
			ft_env.c \
			ft_exit.c \
			ft_export_utils.c \
			ft_export.c \
			ft_pwd.c \
			ft_unset.c \
			builtins_handler.c \
			ft_execute_utils.c \
			ft_execute.c \
			handle_executable.c \
			path_handler.c \
			signal_handler.c \
			command_lst.c \
			check_quotes.c \
			handle_dollar_utils_2.c \
			handle_dollar_utils.c \
			handle_dollar.c \
			handle_env_var_utils_2.c \
			handle_env_var_utils.c \
			handle_env_var.c \
			handle_quote.c \
			here_doc.c \
			is_complete_cmd_line.c \
			new_readline_join_cmd.c \
			open_files.c \
			redirection_handler.c \
			token_error.c \
			arglen.c \
			check_token.c \
			clean_args.c \
			clean_args_utils.c \
			clean_cmd.c \
			copy_tab.c \
			count_char.c \
			free_data.c \
			free_env_var.c \
			free_tab.c \
			ft_is_atoi.c \
			get_next_word.c \
			get_word_count.c \
			init_data.c \
			lst_to_tab.c \
			split_cmd_line_utils.c \
			split_cmd_line.c \
			tab_len.c \
			main.c \

VPATH = sources:sources/list_handler:sources/utils:sources/parsing:sources/execute:sources/builtins

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
