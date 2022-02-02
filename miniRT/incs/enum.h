#ifndef ENUM_H
# define ENUM_H

typedef enum s_define {
	TRUE		= 1,
	FALSE		= 0,
	SUCCESS		= 0,
	FAIL		= 1,
	EQUAL		= 1,
	DIFFERENT	= 0,
	A			= 0,
	B			= 1,
	C			= 2,
}	t_define;

typedef enum s_error {
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
	INCOMPLETE_FILE_ERROR		= 237,
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
	SPHERE			= 0,
	PLANE			= 1,
	CYLINDER		= 2,
	CAMERA			= 3,
	AMBIENT_LIGHT	= 4,
	DIFFUSE_LIGHT	= 5,
}	t_types;

#endif
