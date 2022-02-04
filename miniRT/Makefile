NAME		= miniRT

NAME_DEBUG	= miniRT_debug

SRC_FILES	= main.c \
			setup.c \
			events.c \
			cleanup.c \
			utils.c \
			$(PARSING) \
			$(RAYTRACING) \
			$(COLOR) \
			$(LIB_MATH)

PARSING = \
			parsing/parsing.c \
			parsing/parsing_error.c \
			parsing/fill_objs.c \
			parsing/fill_scene.c \
			parsing/check.c \
			parsing/obj_list.c \
			parsing/fill_utils.c \

RAYTRACING = \
			raytracing/raytracer.c \
			raytracing/sphere.c \
			raytracing/plane.c \
			raytracing/cylinder.c \
			raytracing/disk.c \
			raytracing/camera.c \

COLOR = \
			color/color_pixel.c \
			color/utils.c \
			color/rgb_check.c \

LIB_MATH = \
			lib_math/vec3_init.c \
			lib_math/vec4_init.c \
			lib_math/vec3_op.c \
			lib_math/vec3_and_const_op.c \
			lib_math/vec3_norm.c \
			lib_math/matrix.c

UNAME		=	$(shell uname)

DEBUG 		= off

OBJS_DIR	= objs

SRC_DIR		= srcs

MLX_DIR		= mlx

ifeq ($(UNAME), Darwin)
	MLX_INC		= mlx_osx
	MLX_FLAG		= $(MLX_DIR)/libmlx_osx.a -framework OpenGL -framework Appkit
else
	MLX_INC		= mlx
	MLX_FLAG	= $(MLX_DIR)/libmlx.a -lXext -lX11 -lm
endif

LIBFT_PATH	=	libft

LIBFT_LIB	=	libft/libft.a

LIBFT_MAKE	=	$(MAKE) --no-print-directory -C $(LIBFT_PATH)

INCLUDE		= ./incs

INC_FILES	= miniRT.h \
			  libft.h \
			  enum.h \
			  error.h \
			  utils.h \
			  struct.h \

OBJS		= $(addprefix $(OBJS_DIR)/, $(SRC_FILES:.c=.o))

INCS		= $(addprefix $(INCLUDE)/, $(INC_FILES))

CC			= clang

CFLAGS		= -Wall -Wextra -Werror -g3
ifeq ($(DEBUG), on)
	CFLAGS += -fsanitize=address
endif

RM			= rm -rf

RESET		= \033[0m
RED			= \033[1;31m
GREEN		= \033[1;32m
YELLOW		= \033[1;33m
BLUE		= \033[1;34m
WHITE		= \033[1;37m
ORANGE		= \033[1;38;5;208m
UP			= \033[A
CUT			= \033[K

$(OBJS_DIR)/%.o: $(SRC_DIR)/%.c $(INCS) $(LIBFT_PATH)/*.c
			@mkdir -p $(@D)
			@$(CC) $(CFLAGS) -I$(INCLUDE) -I$(MLX_INC) -c $< -o $@
			@echo "$(CUT)$(BLUE)clang $(RESET)$(notdir $@)"
			@printf "$(UP)"

all:	$(NAME)

$(NAME):	$(OBJS)
				@$(LIBFT_MAKE)
				@$(CC) $(CFLAGS) $^ -o $@ $(LIBFT_LIB) $(MLX_FLAG)
				@echo "$(CUT)$(GREEN)✔ $(NAME) created$(RESET)"

libft:
		@$(LIBFT_MAKE)

debug:	 $(NAME_DEBUG)	

$(NAME_DEBUG):	$(OBJS) 
					@make DEBUG=on --no-print-directory
					@echo "$(BLUE)[mode DEBUG=on]$(RESET)"

clean:
			@make --no-print-directory -C $(LIBFT_PATH) clean
			@$(RM) $(OBJS) $(OBJS_DIR)
			@echo "$(RED)✘ clean$(RESET)"

fclean:		clean
				@$(RM) $(NAME) $(LIBFT_LIB)
				@$(RM) $(NAME) $(DEBUG)
				@echo "$(RED)✘ fclean$(RESET)"

re:			fclean all

.PHONY:		all clean fclean re debug