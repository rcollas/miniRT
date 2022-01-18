NAME		= miniRT

DEBUG		= philosophers_debug

SRC_FILES	= main.c

OBJS_DIR	= ./objs

SRC_DIR		= ./srcs

MLX_DIR		= ./mlx

MLX_INC		= ./mlx

LIBFT_PATH	=	./libft

LIBFT_LIB	=	libft/libft.a

LIBFT_MAKE	=	$(MAKE) --no-print-directory -C $(LIBFT_PATH)

INC_DIR		= ./incs

INC_FILES	= miniRT.h

OBJS		= $(addprefix $(OBJS_DIR)/, $(SRC_FILES:.c=.o))

INCS		= $(addprefix $(INC_DIR)/, $(INC_FILES))

CC			= clang

CFLAGS		= -Wall -Wextra -Werror -g

RM			= rm -rf

$(OBJS_DIR)/%.o: $(SRC_DIR)/%.c $(INCS)
			@mkdir -p $(@D)
			@$(CC) $(CFLAGS) -I$(INC_DIR) -I$(MLX_INC) -c $< -o $@


all:		$(NAME)

$(NAME):	$(OBJS)
				@$(LIBFT_MAKE)
				@$(CC) $(CFLAGS) $^ -o $@ $(LIBFT_LIB) $(MLX_DIR)/libmlx.a -lXext -lX11
				@echo "$(NAME) created"

clean:
			@make --no-print-directory -C $(LIBFT_PATH) clean
			@$(RM) $(OBJS) $(OBJS_DIR)
			@echo "$(NAME) .o deleted"

fclean:		clean
				@$(RM) $(NAME) $(LIBFT_LIB)
				@$(RM) $(NAME) $(DEBUG)
				@echo "$(NAME) deleted"

re:			fclean all

.PHONY:		all clean fclean re