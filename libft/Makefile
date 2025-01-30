# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mleproux <mleproux@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/17 12:41:45 by mleproux          #+#    #+#              #
#    Updated: 2024/12/19 10:54:16 by mleproux         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

COMPILER = cc

FLAGS = -Wall -Werror -Wextra

SOURCES_FILE = sources

SOURCES = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
             ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c \
             ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c \
             ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c \
             ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c \
             ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c \
             ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c \
             ft_uitoa.c ft_lstnew.c ft_lstclear.c ft_lstlast.c \
             ft_lstsize.c ft_lstdelone.c ft_lstadd_back.c \
			 ft_lstadd_front.c ft_lstmap.c ft_lstiter.c \
			 ft_printf.c ft_putchar.c ft_puthex.c ft_putnbr.c ft_putposnbr.c \
			 ft_putptr.c ft_putstr.c get_next_line.c ft_strndup.c ft_lstprint.c \
			 ft_atol.c ft_isspace.c

MY_SOURCES = $(addprefix $(SOURCES_FILE)/, $(SOURCES))
MY_OBJECTS = $(MY_SOURCES:.c=.o)

YELLOW = \033[1;33m
CYAN = \033[0;36m
GREEN = \033[0;32m
RESET = \033[0m

$(NAME): $(MY_OBJECTS)
	@$(MAKE) msg
	@ar rcs $(NAME) $(MY_OBJECTS) $@
	@echo "$(GREEN)Successfully compiled $(CYAN)$(NAME)$(GREEN)!$(RESET)"

.c.o :
	@$(COMPILER) $(FLAGS) -c $< -o $@

msg: 
	@echo "$(YELLOW)Compiling library $(CYAN)$(NAME)$(YELLOW)...$(RESET)"

clean:
	@rm -f $(MY_OBJECTS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

all: $(NAME)

