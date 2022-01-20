#ifndef MINIRT_H
# define MINIRT_H

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
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
	ARG_NUMBER_ERROR = 252
}	t_error;

int parsing(char **argv, int argc);
int parsing_error(int errnum, char *str);

#endif
