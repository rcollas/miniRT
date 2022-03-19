#ifndef ERROR_H
# define ERROR_H

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include "enum_bonus.h"
# include "struct_bonus.h"

int		parsing_error(int errnum, char *str);
int		is_dir_error(char *str);
void	exit_error(int errnum, char *error_msg, t_data *data);
void	exit_error_parsing(int errnum, char *error_msg, t_parsing *parsing_var);
void	exit_error_parsing_end(int errnum, char *error_msg,
			t_parsing *parsing_var, _Bool need_destroy_texture);
int		error(int errnum, char *str);

#endif
