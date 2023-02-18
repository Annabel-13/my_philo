NAME		= philo_bonus
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -g #-fsanitize=address
RM			= /bin/rm -f

INCLUDE_DIR	= incl

INCLUDES 	= -I$(INCLUDE_DIR)

BUILD_DIR	= build
SRC_DIR		= ./src
SRCS		=	main_bonus.c \
				table_and_philo_init_bonus.c \
				philo_life_circle_bonus.c \
				eat_sleep_think_repeat_bonus.c \
				utils.c

OBJS =	$(SRCS:%.c=$(BUILD_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJS): $(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@$(CC) -g $(CFLAGS) $(INCLUDES) -c $< -o $@

bonus: all

re: fclean all

cbuild:
	-$(RM) -r $(BUILD_DIR)

clean:
	$(RM) -r $(BUILD_DIR)

fclean: clean
	$(RM) $(NAME)

.PHONY: all clean fclean re
