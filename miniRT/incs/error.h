#ifndef MINI_RT_ERROR_H
#define MINI_RT_ERROR_H

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include "enum.h"
# include "struct.h"

int		parsing_error(int errnum, char *str);
int		is_dir_error(char *str);
void	exit_error(t_data *data);
int		error(int errnum, char *str);

#endif
