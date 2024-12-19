# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lmoricon <lmoricon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/07 19:33:09 by lmoricon          #+#    #+#              #
#    Updated: 2024/12/08 20:12:25 by lmoricon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Check if readline library is installed on Linux or Mac, if not show message
CURRENT_OS = $(uname -s)
ifeq ($(CURRENT_OS), Linux)
check_readline:
	@test -f /usr/include/readline/readline.h || { echo "Readline library \
		not found. Please install it using the following command:"; \
		echo "sudo apt-get install make libreadline-dev"; \
		exit 1; }
else ifeq ($(CURRENT_OS), Darwin)
	READLINE_DIR := $(shell if [ -d ~/.brew/opt/readline ]; then \
		echo ~/.brew/opt/readline; \
		else if [ -d /usr/local/opt/readline ]; \
		then echo /usr/local/opt/readline; \
		else echo "Readline library not found. Please install it via"; \
			echo "brew install readline"; \
			exit 1; \
		fi; fi)
	INCS = -I $(READLINE_DIR)/include
	LIBS = -L $(READLINE_DIR)/lib
endif

NAME 		= minishell
CFLAGS 		= -Wall -Wextra -Werror -g
CC 			= cc
SRC_DIR 	= src
OBJ_DIR 	= obj
LIBFT_DIR 	= libft
LIBFT 		= libft/libft.a
RM 			= rm -rf

SRC = main.c tokenizer.c utils_token.c parser.c utils_parse.c utils.c memory_management.c eggxecutor.c utils_exec.c expander.c \
	  builtin/cd.c builtin/echo.c builtin/exit.c builtin/pwd.c builtin/env.c	builtin/export.c	builtin/unset.c	quote_expander.c\
		heredoc.c signals.c exp.c
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ_DIR) $(OBJ)
	@echo "Compiling minishell..."
	@$(CC) $(INCS) $(LIBS)  $(CFLAGS) $(OBJ) $(LIBFT) -lreadline -o $@
	@echo "Done!"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c  $< -o $@

$(LIBFT):
	@echo "Compiling libft..."
	@make -s -C libft
	@make bonus -s -C libft

clean:
	@echo "Cleaning..."
	@make clean -s -C libft
	@$(RM) $(OBJ_DIR)

fclean: clean
	@echo "Fcleaning..."
	@$(RM) $(NAME)
	@make fclean -s -C libft

git: fclean
	git add .
	git commit -m "update"
	git push

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/builtin

re: fclean all

.PHONY: all clean fclean re
