#ifndef MINIRT_H
# define MINIRT_H

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include "mlx.h"
# ifdef __linux__
# include "mlx_int.h"
# endif
# include "libft.h"
# include "error.h"
# include "enum.h"
# include "struct.h"
# include "utils.h"

t_mlx	*setup_mlx(void);
void	events_loop(t_mlx *mlx);
void	clean_mlx(t_mlx *mlx);
int		parsing(char **argv, int argc);
void	ft_free(void *to_free);

#endif
