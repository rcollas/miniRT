/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enum_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:47:08 by efrancon          #+#    #+#             */
/*   Updated: 2022/03/25 14:03:20 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUM_BONUS_H
# define ENUM_BONUS_H

# define SPECULAR_COEFF 64
# define NO_SHADOW 1.0f
# define PATH_TRACING_COEFF 0.3f
# define LIGHT_INTENSITY 3.0f
# define RESET "\033[0m"
# define ORANGE "\033[38;5;215m"
# define YELLOW "\033[38;5;229m"
# define GREEN "\033[38;5;121m"
# define GREY "\033[38;5;243m"
# define LIGHT_GREY "\033[38;5;249m"

# define INT_MIN	-2147483648

typedef enum s_define
{
	TRUE				= 1,
	FALSE				= 0,
	SUCCESS				= 0,
	FAIL				= 1,
	EQUAL				= 1,
	DIFFERENT			= 0,
	A					= 0,
	C					= 1,
	X					= 0,
	Y					= 1,
	Z					= 2,
	R					= 0,
	G					= 1,
	B					= 2,
	T					= 3,
	U					= 0,
	V					= 1,
	NO_PATH_TRACING		= 0,
	PATH_TRACING		= 1,
	CLASSIC_LIGHTING	= 0,
	PHONG_LIGHTING		= 1,
	NO_MULTITHREADING	= 0,
	MULTITHREADING		= 1,
	RANDOM_DIR_LOCAL	= 0,
	RANDOM				= 1,
	TANGENT_1			= 2,
	TANGENT_2			= 3,
	CHECKER				= 1,
	NORMAL				= 2,
	BUMP_MAP			= 3,
	DIFFUSE				= 0,
	SPECULAR			= 1,
	NO_TEXTURE			= 0,
	HAS_TEXTURE			= 1,
	NO_DESTROY_TEXTURE	= 0,
	DESTROY_TEXTURE		= 1,
}	t_define;

typedef enum s_error
{
	OPEN_ERROR					= 255,
	CLOSE_ERROR					= 254,
	READ_ERROR					= 253,
	MALLOC_ERROR				= 252,
	STRJOIN_ERROR				= 251,
	STRDUP_ERROR				= 250,
	EXTENSION_ERROR				= 249,
	ARG_NUMBER_ERROR			= 248,
	IS_DIR_ERROR				= 247,
	FILE_ERROR					= 246,
	INVALID_TYPE_ERROR			= 245,
	AMBIENT_LIGHT_FORMAT_ERROR	= 243,
	CAMERA_FORMAT_ERROR			= 242,
	DIFFUSE_LIGHT_FORMAT_ERROR	= 241,
	SPHERE_FORMAT_ERROR			= 240,
	PLANE_FORMAT_ERROR			= 239,
	CYLINDER_FORMAT_ERROR		= 238,
	DISK_FORMAT_ERROR			= 237,
	CONE_FORMAT_ERROR			= 236,
	SQUARE_FORMAT_ERROR			= 235,
	SKY_FORMAT_ERROR			= 234,
	INCOMPLETE_FILE_ERROR		= 233,
	MLX_ERROR					= 232,
	INCORRECT_FILENAME			= 231,
	INCORRECT_SIZE_WINDOW		= 230,
}	t_error;

# ifdef __linux__

typedef enum s_key
{
	KEY_ESC		= 65307,
	KEY_LEFT	= 65361,
	KEY_RIGHT	= 65363,
	KEY_DOWN	= 65364,
	KEY_UP		= 65362,
	KEY_W		= 119,
	KEY_A		= 97,
	KEY_S		= 115,
	KEY_D		= 100,
	KEY_P		= 112,
	KEY_SPACE	= 32,
	KEY_MAJ		= 65505,
	KEY_ENTER	= 65293,
}	t_key;
#  define IS_LINUX 1
# else

typedef enum s_key
{
	KEY_ESC		= 53,
	KEY_LEFT	= 123,
	KEY_RIGHT	= 124,
	KEY_DOWN	= 125,
	KEY_UP		= 126,
	KEY_W		= 13,
	KEY_A		= 0,
	KEY_S		= 1,
	KEY_D		= 2,
	KEY_P		= 35,
	KEY_MAJ		= 257,
	KEY_TAB		= 48,
	KEY_SPACE	= 49,
}	t_key;
#  define IS_LINUX 0
# endif

typedef enum s_types
{
	CAMERA			= 1,
	AMBIENT_LIGHT	= 2,
	DIFFUSE_LIGHT	= 3,
	SPHERE			= 4,
	PLANE			= 5,
	CYLINDER		= 6,
	DISK			= 7,
	CONE			= 8,
	SKY				= 9,
	SQUARE			= 10,
}	t_types;

#endif
