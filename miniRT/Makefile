NAME		= miniRT

SRC_FILES	= main.c \
			setup.c \
			events.c \
			cleanup.c \
			utils.c \
			parsing/parsing.c \
			parsing/parsing_error.c

UNAME		:=	$(shell uname)

OBJS_DIR	= objs

SRC_DIR		= srcs

MLX_DIR		= mlx

ifeq ($(UNAME), Darwin)
	MLX_INC		= mlx_osx
else
	MLX_INC		= mlx
endif

LIBFT_PATH	=	libft

LIBFT_LIB	=	libft/libft.a

LIBFT_MAKE	=	$(MAKE) --no-print-directory -C $(LIBFT_PATH)

INC_DIR		= ./incs

INC_FILES	= miniRT.h \
			  libft.h \
			  enum.h \
			  error.h \
			  utils.h \
			  struct.h \

OBJS		= $(addprefix $(OBJS_DIR)/, $(SRC_FILES:.c=.o))

INCS		= $(addprefix $(INC_DIR)/, $(INC_FILES))

CC			= clang

CFLAGS		= -Wall -Wextra -Werror -g3

RM			= rm -rf

RESET		= \033[0m
RED			= \033[1;31m
GREEN		= \033[1;32m
YELLOW		= \033[1;33m
BLUE		= \033[1;34m
WHITE		= \033[1;37m

$(OBJS_DIR)/%.o: $(SRC_DIR)/%.c $(INCS) $(LIBFT_PATH)/*.c
			@mkdir -p $(@D)
			@$(CC) $(CFLAGS) -I$(INC_DIR) -I$(MLX_INC) -c $< -o $@
			@echo "$(BLUE)clang $(RESET)$(notdir $@)"

all:		$(NAME)

ifeq ($(UNAME), Darwin)
$(NAME):	$(OBJS)
				@$(LIBFT_MAKE)
				@$(CC) $(CFLAGS) $^ -o $@ $(LIBFT_LIB) $(MLX_DIR)/libmlx_osx.a -framework OpenGL -framework Appkit
				@echo "$(GREEN)$(NAME) created$(RESET)"
else
$(NAME):	$(OBJS)
				@$(LIBFT_MAKE)
				@$(CC) $(CFLAGS) $^ -o $@ $(LIBFT_LIB) $(MLX_DIR)/libmlx.a -lXext -lX11
				@echo "$(GREEN)$(NAME) created$(RESET)"
endif

clean:
			@make --no-print-directory -C $(LIBFT_PATH) clean
			@$(RM) $(OBJS) $(OBJS_DIR)
			@echo "$(RED)clean$(RESET)"

fclean:		clean
				@$(RM) $(NAME) $(LIBFT_LIB)
				@$(RM) $(NAME) $(DEBUG)
				@echo "$(RED)fclean$(RESET)"

re:			fclean all

.PHONY:		all clean fclean re