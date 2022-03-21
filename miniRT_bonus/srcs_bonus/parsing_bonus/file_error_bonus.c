#include "miniRT_bonus.h"

int	extension_error(char *str)
{
	ft_putstr_fd("Extension error: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": Is invalid\n", 2);
	return (EXTENSION_ERROR);
}

int	arg_nb_error(void)
{
	ft_putstr_fd("Argument error: ", 2);
	ft_putstr_fd("MiniRT needs a unique .rt file as argument\n", 2);
	return (ARG_NUMBER_ERROR);
}

int	is_dir_error(char *str)
{
	ft_putstr_fd("Argument error: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": Is a directory\n", 2);
	return (IS_DIR_ERROR);
}

int	file_error(char *str)
{
	ft_putstr_fd("Argument error: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	return (errno);
}

int	incomplete_file_error(char *str)
{
	ft_putstr_fd("File is incomplete: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n\033[38;5;121m.rt must contain at least one camera C,"
		" one diffuse light L and one ambient light A\033[0m\n", 2);
	return (INCOMPLETE_FILE_ERROR);
}
