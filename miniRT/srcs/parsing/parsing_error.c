# include "miniRT.h"

int	extension_error(char *str)
{
	ft_putstr_fd("Extension error: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(" is invalid\n", 2);
	return (EXTENSION_ERROR);
}

int	arg_nb_error(void)
{
	ft_putstr_fd("Argument error: ", 2);
	ft_putstr_fd("miniRT needs a unique .rt file as argument\n", 2);
	return (ARG_NUMBER_ERROR);
}

int parsing_error(int errnum, char *str)
{
	ft_putstr_fd("Error\n", 2);
	if (errnum == EXTENSION_ERROR)
		return (extension_error(str));
	if (errnum == ARG_NUMBER_ERROR)
		return (arg_nb_error());
	return (0);
}