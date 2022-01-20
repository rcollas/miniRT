#ifndef MINI_RT_ENUM_H
#define MINI_RT_ENUM_H

typedef enum s_define {
	TRUE		= 1,
	FALSE		= 0,
	SUCCESS		= 0,
	FAIL		= 1,
	EQUAL		= 1,
	DIFFERENT	= 0
}	t_define;

typedef enum s_error {
	OPEN_ERROR			= 255,
	CLOSE_ERROR			= 254,
	READ_ERROR			= 253,
	MALLOC_ERROR		= 252,
	STRJOIN_ERROR		= 251,
	EXTENSION_ERROR		= 250,
	ARG_NUMBER_ERROR	= 249,
	IS_DIR_ERROR		= 248,
	FILE_ERROR			= 247
}	t_error;

# ifdef __linux__

typedef enum s_key
{
	KEY_ESC		= 65307,
	KEY_LEFT	= 65361,
	KEY_RIGHT	= 65363,
	KEY_DOWN	= 65364,
	KEY_UP		= 65362,
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
}	t_key;
#  define IS_LINUX 0
# endif

typedef enum s_types
{
	AMBIENT_LIGHT	= 1,
	DIFFUSE_LIGHT	= 2,
	CAMERA			= 3,
	SPHERE			= 4,
	CYLINDER		= 5,
	PLAN			= 6,
}	t_types;

#endif
