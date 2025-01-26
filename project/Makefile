NAME = libftprintf.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I.

RESET = \033[0m
BOLD = \033[1m
GREEN = \033[92m
YELLOW = \033[33m


SRC_DIR := src
SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ = ${SRC:.c=.o}

all: $(NAME)

simple_test:
	$(CC) simple_example.c $(NAME)
	./a.out

full_test:
	$(CC) full_test.c $(NAME)
	./a.out

how_to_use:
	cat how_to_use.txt

$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo "$(BOLD)$(GREEN)😎      ft_printf Compiled      😎$(RESET)"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)
	@echo "$(BOLD)$(YELLOW)🧹     Cleaned .o files     🧹$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(BOLD)$(YELLOW)🧹     Cleaned .a files     🧹$(RESET)"

re: fclean all
