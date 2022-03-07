#ifndef ERROR_H
# define ERROR_H

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include "enum.h"
# include "struct.h"

int		parsing_error(int errnum, char *str);
int		is_dir_error(char *str);
void	exit_error(int errnum, char *error_msg, t_data *data);
void	exit_error_parsing(int errnum, char *error_msg, t_parsing *parsing_var);
int		error(int errnum, char *str);

#endif
