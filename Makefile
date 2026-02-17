NAME = minishell

SRC = src/main.c \
		src/builtins/env_setup.c \
		src/builtins/env_utils.c \
		src/cleanup/cleanup.c \
		src/cleanup/free.c \
		src/lexer/lexer_utils.c \
		src/lexer/lexer.c \
		src/parser/parser_utils.c \
		src/parser/parser.c \
		src/proves.c

######  EXECUTOR FILES:

EX_SRC_DIR = src/executor/

EX_SRC_NAMES = cmd_handler.c \
			   pipex_utils_bonus.c \
			   pipex_utils_2_bonus.c \
			   pipex_utils_3_bonus.c

EX_SRC = $(addprefix $(EX_SRC_DIR), $(EX_SRC_NAMES))

SRC += $(EX_SRC)

######  BUILT-IN FILES:

BI_SRC_DIR = src/builtins/

BI_SRC_NAMES = my_execve.c \
			   my_echo.c \
			   my_cd.c \
			   my_pwd.c \
			   my_export.c \
			   my_unset.c \
			   my_env.c \
			   my_exit.c

BI_SRC = $(addprefix $(BI_SRC_DIR), $(BI_SRC_NAMES))

SRC += $(BI_SRC)

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
