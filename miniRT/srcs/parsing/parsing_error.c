#include "miniRT.h"

void	error_intensity(void)
{
	ft_putstr_fd("[INTENSITY] 0.0-1.0   ", 2);
}

void	file_format_error(void)
{
	ft_putstr_fd("File format error\n\n", 2);
	ft_putstr_fd("\033[1;31m    Yours:   ", 2);
}

int	invalid_type_error(char *str)
{
	ft_putstr_fd("File format error\n\n", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	ft_putstr_fd("Invalid type error: "
		"Available types are: A C L sp pl cy\n\n", 2);
	return (INVALID_TYPE_ERROR);
}

int	parsing_error(int errnum, char *str)
{
	ft_putstr_fd("Error: ", 2);
	if (errnum == EXTENSION_ERROR)
		return (extension_error(str));
	if (errnum == ARG_NUMBER_ERROR)
		return (arg_nb_error());
	if (errnum == IS_DIR_ERROR)
		return (is_dir_error(str));
	if (errnum == FILE_ERROR)
		return (file_error(str));
	if (errnum == INCOMPLETE_FILE_ERROR)
		return (incomplete_file_error(str));
	return (0);
}

int	error(int errnum, char *str)
{
	ft_putstr_fd("Error: ", 2);
	if (errnum == CLOSE_ERROR)
		return (close_error(str));
	if (errnum == READ_ERROR)
		return (read_error(str));
	if (errnum == STRJOIN_ERROR)
		return (strjoin_error());
	if (errnum == AMBIENT_LIGHT_FORMAT_ERROR)
		return (ambient_light_format_error(str));
	if (errnum == CAMERA_FORMAT_ERROR)
		return (camera_format_error(str));
	if (errnum == DIFFUSE_LIGHT_FORMAT_ERROR)
		return (diffuse_light_format_error(str));
	if (errnum == SPHERE_FORMAT_ERROR)
		return (sphere_format_error(str));
	if (errnum == PLANE_FORMAT_ERROR)
		return (plane_format_error(str));
	if (errnum == CYLINDER_FORMAT_ERROR)
		return (cylinder_format_error(str));
	if (errnum == INVALID_TYPE_ERROR)
		return (invalid_type_error(str));
	return (0);
}
