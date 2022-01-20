# include "miniRT.h"

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
	ft_putstr_fd(": Is a directory", 2);
	return (IS_DIR_ERROR);
}

int	access_error(char *str)
{
	ft_putstr_fd("Argument error: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(EACCES), 2);
	return (EACCES);
}

int	file_not_found(char *str)
{
	ft_putstr_fd("Argument error: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(ENOENT), 2);
	return (ENOENT);
}

int parsing_error(int errnum, char *str)
{
	ft_putstr_fd("Error\n", 2);
	if (errnum == EXTENSION_ERROR)
		return (extension_error(str));
	if (errnum == ARG_NUMBER_ERROR)
		return (arg_nb_error());
	if (errnum == IS_DIR_ERROR)
		return (is_dir_error(str));
	if (errnum == EACCES)
		return (access_error(str));
	if (errnum == ENOENT)
		return (file_not_found(str));
	return (0);
}