#ifndef MINI_RT_ERROR_H
#define MINI_RT_ERROR_H

# include "enum.h"
# include "struct.h"

int		parsing_error(int errnum, char *str);
int		is_dir_error(char *str);
void	exit_error(t_mlx *mlx);
int		error(int errnum, char *str);

#endif
