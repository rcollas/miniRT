#ifndef MINIRT_H
# define MINIRT_H

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include "mlx.h"
# include "mlx_int.h"
# include "libft.h"

typedef enum s_define {
	TRUE = 1,
	FALSE = 0,
	SUCCESS = 0,
	FAIL = 1,
	EQUAL = 1,
	DIFFERENT = 0
}	t_define;

typedef enum s_error {
	OPEN_ERROR = 255,
	MALLOC_ERROR = 254,
	EXTENSION_ERROR = 253,
	ARG_NUMBER_ERROR = 252,
	IS_DIR_ERROR = 251
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

typedef struct s_coord
{
	float	x;
	float	y;
	float	z;
}	t_coord;

typedef struct s_vector
{
	float	x;
	float	y;
	float	z;
}	t_vector;

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

typedef struct s_mlx
{
	void		*ptr;
	void		*window;
	void		*image;
	char		*addr;
	int			bpp;
	int			size_line;
	int			endian;
}				t_mlx;

t_mlx	*setup_mlx(void);
void	events_loop(t_mlx *mlx);
void	clean_mlx(t_mlx *mlx);
void	exit_error(t_mlx *mlx);
int		parsing(char **argv, int argc);
int		parsing_error(int errnum, char *str);
int		is_dir_error(char *str);

#endif
