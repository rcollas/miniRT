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
	C			= 1,
	X			= 0,
	Y			= 1,
	Z			= 2,
	R			= 0,
	G			= 1,
	B			= 2,
	T			= 3,
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
	DISK_FORMAT_ERROR			= 237,
	INCOMPLETE_FILE_ERROR		= 236,
}	t_error;

# ifdef __linux__

typedef enum s_key
{
	KEY_ESC		= 65307,
	KEY_LEFT	= 65361,
	KEY_RIGHT	= 65363,
	KEY_DOWN	= 65364,
	KEY_UP		= 65362,
	KEY_H		= 104,
	KEY_J		= 106,
	KEY_K		= 107,
	KEY_L		= 108,
	KEY_N		= 110,
	KEY_M		= 109,
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
	KEY_H		= 4,
	KEY_J		= 38,
	KEY_K		= 40,
	KEY_L		= 37,
	KEY_N		= 45,
	KEY_M		= 46,
	KEY_ENTER	= 36,
	KEY_MAJ		= 257,
	KEY_TAB		= 48,
}	t_key;
#  define IS_LINUX 0
# endif

typedef enum s_types
{
	SPHERE			= 0,
	PLANE			= 1,
	CYLINDER		= 2,
	DISK			= 3,
	CAMERA			= 4,
	AMBIENT_LIGHT	= 5,
	DIFFUSE_LIGHT	= 6,
}	t_types;

#endif
