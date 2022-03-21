NAME		= miniRT

BONUS_NAME	= miniRT_bonus

NAME_DEBUG	= miniRT_debug

SRC_FILES	= main.c \
			$(UTILS) \
			$(PARSING) \
			$(RAYTRACING) \
			$(OBJECTS) \
			$(LIGHTING) \
			$(LIB_MATH) \

UTILS = \
			utils/setup.c \
			utils/events.c \
			utils/cleanup.c \
			utils/safe_functions.c \
			utils/display.c \
			utils/print.c \
			utils/exit_error.c \

PARSING = \
			parsing/parsing.c \
			parsing/parsing_error.c \
			parsing/fill_objs.c \
			parsing/fill_scene.c \
			parsing/check.c \
			parsing/obj_list.c \
			parsing/fill_utils.c \
			parsing/utils.c \
			parsing/convert_list_to_tab.c \
			parsing/load_file.c \
			parsing/free.c \
			parsing/check_objs.c \
			parsing/check_scene.c \
			parsing/objs_error.c \
			parsing/file_error.c \
			parsing/function_error.c \
			parsing/scene_error.c \
			parsing/syntax_error.c \

RAYTRACING = \
			raytracing/raytracer.c \
			raytracing/camera_init.c \
			raytracing/hit_init.c \
			raytracing/camera_move.c \

OBJECTS = \
			objects/sphere.c \
			objects/plane.c \
			objects/cylinder.c \
			objects/utils.c \

LIGHTING = \
			lighting/shadow.c \
			lighting/light.c \
			lighting/color_create.c \
			lighting/color_check.c \

LIB_MATH = \
			lib_math/vec2_op.c \
			lib_math/vec3_init.c \
			lib_math/vec3_op1.c \
			lib_math/vec3_op2.c \
			lib_math/vec3_op3.c \
			lib_math/vec3_norm.c \
			lib_math/vec4_init.c \
			lib_math/vec4_norm.c \
			lib_math/matrix.c \
			lib_math/trigo.c \
			lib_math/frand.c \
			lib_math/algebra.c

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

LIBFT_MAKE	=	$(MAKE) bonus --no-print-directory -C $(LIBFT_PATH)

MLX_MAKE	=	$(MAKE) --no-print-directory -C $(MLX_DIR)

INCLUDE_DIR	= ./incs

INC_FILES	= miniRT.h \
			  libft.h \
			  enum.h \
			  error.h \
			  utils.h \
			  struct.h \
			  lib_math.h \

OBJS				= $(addprefix $(OBJS_DIR)/, $(SRC_FILES:.c=.o))

INCLUDE				= $(addprefix $(INCLUDE_DIR)/, $(INC_FILES))

CC			= clang

CFLAGS		= -Wall -Wextra -Werror -pthread -g3
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


$(OBJS_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDE) $(LIBFT_PATH)/*.c
			@mkdir -p $(@D)
			@$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -I$(MLX_INC) -c $< -o $@
			@echo "$(CUT)$(BLUE)clang $(RESET)$(notdir $@)"
			@printf "$(UP)"

all:	$(NAME)

$(NAME):	$(OBJS)
				@$(LIBFT_MAKE)
				@$(MLX_MAKE)
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
			@make --no-print-directory -C $(MLX_DIR) clean
			@$(RM) $(OBJS) $(OBJS_DIR)
			@echo "$(RED)✘ clean$(RESET)"

fclean:		clean
				@$(RM) $(NAME) $(LIBFT_LIB)
				@$(RM) $(NAME) $(DEBUG_NAME)
				@echo "$(RED)✘ fclean$(RESET)"

re:			fclean all

.PHONY:		all clean fclean re debug
