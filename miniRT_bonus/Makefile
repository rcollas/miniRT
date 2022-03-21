NAME		= miniRT

BONUS_NAME	= miniRT_bonus

NAME_DEBUG	= miniRT_debug

SRC_FILES_BONUS	= main_bonus.c \
				$(UTILS_BONUS) \
				$(PARSING_BONUS) \
				$(RAYTRACING_BONUS) \
				$(TEXTURE_BONUS) \
				$(OBJECTS_BONUS) \
				$(LIGHTING_BONUS) \
				$(LIB_MATH_BONUS) \
				$(OPT_UTILS_BONUS)

OPT_UTILS_BONUS = \
			utils_bonus/timestamp_bonus.c \

UTILS_BONUS = \
			utils_bonus/setup_bonus.c \
			utils_bonus/events_bonus.c \
			utils_bonus/cleanup_bonus.c \
			utils_bonus/safe_functions_bonus.c \
			utils_bonus/display_bonus.c \
			utils_bonus/print_bonus.c \
			utils_bonus/exit_error_bonus.c \

PARSING_BONUS = \
			parsing_bonus/parsing_bonus.c \
			parsing_bonus/parsing_error_bonus.c \
			parsing_bonus/fill_objs_bonus.c \
			parsing_bonus/fill_objs_bonus_bonus.c \
			parsing_bonus/fill_scene_bonus.c \
			parsing_bonus/check_bonus.c \
			parsing_bonus/obj_list_bonus.c \
			parsing_bonus/fill_utils_bonus.c \
			parsing_bonus/utils_bonus.c \
			parsing_bonus/convert_list_to_tab_bonus.c \
			parsing_bonus/load_file_bonus.c \
			parsing_bonus/check_objs_format_bonus.c \
			parsing_bonus/check_objs_format2_bonus.c \
			parsing_bonus/check_scene_format_bonus.c \
			parsing_bonus/check_objs_bonus.c \
			parsing_bonus/file_error_bonus.c \
			parsing_bonus/fill_light_bonus.c \
			parsing_bonus/get_obj_info_bonus.c \
			parsing_bonus/check_objs_bonus.c \
			parsing_bonus/check_scene_bonus.c \
			parsing_bonus/get_obj_bonus_bonus.c \
			parsing_bonus/free_bonus.c \
			parsing_bonus/function_error_bonus.c \
			parsing_bonus/format_error_bonus.c \
			parsing_bonus/format_error2_bonus.c \

RAYTRACING_BONUS = \
			raytracing_bonus/raytracer_bonus.c \
			raytracing_bonus/path_tracing_bonus.c \
			raytracing_bonus/multithreading_bonus.c \
			raytracing_bonus/camera_init_bonus.c \
			raytracing_bonus/camera_move_bonus.c \
			raytracing_bonus/init_ray_bonus.c \

TEXTURE_BONUS = \
			texture_bonus/parsing_bonus.c \
			texture_bonus/uv_mapping_bonus.c \
			texture_bonus/checker_bonus.c \
			texture_bonus/texture_bonus.c \
			texture_bonus/bump_map_bonus.c \
			texture_bonus/check_texture.c \

OBJECTS_BONUS = \
			objects_bonus/sphere_bonus.c \
			objects_bonus/plane_bonus.c \
			objects_bonus/cylinder_bonus.c \
			objects_bonus/disk_bonus.c \
			objects_bonus/utils_bonus.c \
			objects_bonus/cone_bonus.c \
			objects_bonus/cone_utils_bonus.c \
			objects_bonus/square_bonus.c \

LIGHTING_BONUS = \
			lighting_bonus/shadow_bonus.c \
			lighting_bonus/light_bonus.c \
			lighting_bonus/phong_light_bonus.c \
			lighting_bonus/color_create_bonus.c \
			lighting_bonus/color_check_bonus.c \

LIB_MATH_BONUS = \
			lib_math_bonus/vec2_op_bonus.c \
			lib_math_bonus/vec3_init_bonus.c \
			lib_math_bonus/vec3_op1_bonus.c \
			lib_math_bonus/vec3_op2_bonus.c \
			lib_math_bonus/vec3_op3_bonus.c \
			lib_math_bonus/vec3_norm_bonus.c \
			lib_math_bonus/vec4_init_bonus.c \
			lib_math_bonus/vec4_norm_bonus.c \
			lib_math_bonus/matrix_bonus.c \
			lib_math_bonus/trigo_bonus.c \
			lib_math_bonus/frand_bonus.c \
			lib_math_bonus/algebra_bonus.c \

UNAME		=	$(shell uname)

DEBUG 		= off

OBJS_DIR	= objs_bonus

SRC_DIR_BONUS	= srcs_bonus

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

INCLUDE_DIR_BONUS	= ./incs_bonus

INC_FILES_BONUS	= miniRT_bonus.h \
			 	 libft_bonus.h \
			 	 enum_bonus.h \
			 	 error_bonus.h \
			 	 utils_bonus.h \
			 	 struct_bonus.h \
			 	 lib_math_bonus.h \

OBJS_BONUS			= $(addprefix $(OBJS_DIR)/, $(SRC_FILES_BONUS:.c=.o))

INCLUDE_BONUS		= $(addprefix $(INCLUDE_DIR_BONUS)/, $(INC_FILES_BONUS))

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


$(OBJS_DIR)/%.o: $(SRC_DIR_BONUS)/%.c $(INCLUDE_BONUS) $(LIBFT_PATH)/*.c
			@mkdir -p $(@D)
			@$(CC) $(CFLAGS) -I$(INCLUDE_DIR_BONUS) -I$(MLX_INC) -c $< -o $@
			@echo "$(CUT)$(BLUE)clang $(RESET)$(notdir $@)"
			@printf "$(UP)"

all:	$(BONUS_NAME)

bonus:	$(BONUS_NAME)

$(BONUS_NAME):	$(OBJS_BONUS)
					@$(LIBFT_MAKE)
					@$(CC) $(CFLAGS) $^ -o $@ $(LIBFT_LIB) $(MLX_FLAG)
					@echo "$(CUT)$(GREEN)✔ $(BONUS_NAME) created$(RESET)"

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
				@$(RM) $(NAME) $(BONUS_NAME)$(DEBUG_NAME)
				@echo "$(RED)✘ fclean$(RESET)"

re:			fclean all

.PHONY:		all clean fclean re debug bonus