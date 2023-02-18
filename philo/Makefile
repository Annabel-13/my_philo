NAME = philo
SRC = src
OBJ = obj
CC = gcc
CFLAGS = -Werror -Wextra -Wall -pthread -g -fsanitize=thread
SRC_F = $(wildcard $(SRC)/*.c)

#================================================================================

RED		=	\033[1;31m
BLUE	=	\033[1;34m
YELLOW	=	\033[1;33m
GRN		=	\033[32m
GRN_B	=	\033[1;32m
WHT		=	\x1B[37m
PUPURE	=	\033[1;35m
MAG		=	\x1B[35m
GRY		=	\033[1;30m
TURQUOISE =	\033[36;1m
END		=	\033[0m

#================================================================================

all: $(NAME)

$(NAME):
	@$(CC) $(FLAGS) $(SRC_F) -o $@
	@echo "$(GRN)Philosophers compiled!$(DEF_COLOR)"

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)
	@echo "$(YELLOW)Everything was cleaned $(DEF_COLOR)"
re: fclean all