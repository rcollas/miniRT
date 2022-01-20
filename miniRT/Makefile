NAME		= miniRT

DEBUG		= philosophers_debug

SRC_FILES	= main.c \
			setup.c \
			events.c \
			cleanup.c \
			parsing/parsing.c \
			parsing/parsing_error.c

OBJS_DIR	= objs

SRC_DIR		= srcs

MLX_DIR		= mlx

MLX_INC		= mlx

LIBFT_PATH	=	libft

LIBFT_LIB	=	libft/libft.a

LIBFT_MAKE	=	$(MAKE) --no-print-directory -C $(LIBFT_PATH)

INC_DIR		= ./incs

INC_FILES	= miniRT.h\
			  libft.h

OBJS		= $(addprefix $(OBJS_DIR)/, $(SRC_FILES:.c=.o))

INCS		= $(addprefix $(INC_DIR)/, $(INC_FILES))

CC			= clang

CFLAGS		= -Wall -Wextra -Werror -g3

RM			= rm -rf

RESET		= \033[0m
GREEN		= \033[32m
BLUE		= \033[34m
YELLOW		= \033[33m

$(OBJS_DIR)/%.o: $(SRC_DIR)/%.c $(INCS) $(LIBFT_PATH)/*.c
			@mkdir -p $(@D)
			@$(CC) $(CFLAGS) -I$(INC_DIR) -I$(MLX_INC) -c $< -o $@
			@echo "$(BLUE)clang $(RESET)$(notdir $@)"


all:		$(NAME)

$(NAME):	$(OBJS)
				@$(LIBFT_MAKE)
				@$(CC) $(CFLAGS) $^ -o $@ $(LIBFT_LIB) $(MLX_DIR)/libmlx.a -lXext -lX11
				@echo "$(GREEN)$(NAME) created$(RESET)"

clean:
			@make --no-print-directory -C $(LIBFT_PATH) clean
			@$(RM) $(OBJS) $(OBJS_DIR)
			@echo "$(YELLOW)objects $(NAME) removed$(RESET)"

fclean:		clean
				@$(RM) $(NAME) $(LIBFT_LIB)
				@$(RM) $(NAME) $(DEBUG)
				@echo "$(YELLOW)$(NAME) deleted$(RESET)"

re:			fclean all

.PHONY:		all clean fclean re