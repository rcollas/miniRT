#ifndef MINIRT_H
# define MINIRT_H

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "mlx.h"
# include "mlx_int.h"

typedef enum s_define {
	TRUE = 1,
	FALSE = 0,
	SUCCESS = 0,
	FAIL = 1
}	t_define;

typedef enum s_error {
	OPEN_ERROR = 255,
	MALLOC_ERROR = 254,
}	t_error;

#endif
