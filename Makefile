NAME = minishell
SRC = main.c \
		env_setup.c

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

OBJ_DIR = obj
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)
DEP = $(SRC:%.c=$(OBJ_DIR)/%.d)

CC = cc
CCFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address
LDFLAGS = -lreadline

all: libft $(NAME)

-include $(DEP)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CCFLAGS) $(OBJ) $(LIBFT) -o $(NAME) $(LDFLAGS)

libft:
	$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: %.c $(HEADER) | $(OBJ_DIR)
	mkdir -p $(dir $@)
	$(CC) $(CCFLAGS) -MMD -MP -I $(HEADER_DIR)/ -Ilibft -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR) $(OBJ_DIR_BONUS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all


.PHONY: all bonus clean fclean re libft
