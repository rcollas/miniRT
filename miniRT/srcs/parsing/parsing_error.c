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
	ft_putstr_fd("File error: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": File is incomplete\n", 2);
	ft_putstr_fd(".rt must contain at least one camera C,"
				 " one diffuse light L and one ambient light A\n", 2);
	return (INCOMPLETE_FILE_ERROR);
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
	if (errnum == FILE_ERROR)
		return (file_error(str));
	if (errnum == INCOMPLETE_FILE_ERROR)
		return (incomplete_file_error(str));
	return (0);
}

int	close_error(char *str)
{
	ft_putstr_fd("Close failed: fd ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	ft_free(str);
	return (errno);
}

int	read_error(char *str)
{
	ft_putstr_fd("Read failed: fd ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	ft_free(str);
	return (errno);
}

int	strjoin_error(void)
{
	ft_putstr_fd("Critical error: Strjoin failed\n", 2);
	return (STRJOIN_ERROR);
}

int strdup_error(void)
{
	ft_putstr_fd("Critical error: Strdup failed\n", 2);
	return (STRDUP_ERROR);
}

int	ambient_light_format_error(char *str)
{
	ft_putstr_fd("File format error: \n", 2);
	ft_putstr_fd("Yours: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	ft_putstr_fd("Expected: [ID]:A [INTENSITY]:0.0-1.0 ", 2);
	ft_putstr_fd("[RGB]:0-255,0-255,0-255\n", 2);
	return (AMBIENT_LIGHT_FORMAT_ERROR);
}

int	camera_format_error(char *str)
{
	ft_putstr_fd("File format error: \n", 2);
	ft_putstr_fd("Yours: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	ft_putstr_fd("Expected: [ID]:C [COORDINATES]:0.0,0.0,0.0 ", 2);
	ft_putstr_fd("[VERTEX]:0.0,0.0,0.0 [RGB]:0-255,0-255,0-255 \n", 2);
	return (CAMERA_FORMAT_ERROR);
}

int	diffuse_light_format_error(char *str)
{
	ft_putstr_fd("File format error: \n", 2);
	ft_putstr_fd("Yours: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	ft_putstr_fd("Expected: [ID]:L [COORDINATES]:0.0,0.0,0.0 ", 2);
	ft_putstr_fd("[INTENSITY]:0.0-1.0\n", 2);
	return (DIFFUSE_LIGHT_FORMAT_ERROR);
}

int	sphere_format_error(char *str)
{
	ft_putstr_fd("File format error: \n", 2);
	ft_putstr_fd("Yours: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	ft_putstr_fd("Expected: [ID]:sp [COORDINATES]:0.0,0.0,0.0 ", 2);
	ft_putstr_fd("[DIAMETER]:0.0 [RGB]:0-255,0-255,0-255 \n", 2);
	return (SPHERE_FORMAT_ERROR);
}

int	plan_format_error(char *str)
{
	ft_putstr_fd("File format error: \n", 2);
	ft_putstr_fd("Yours: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	ft_putstr_fd("Expected: [ID]:pl [COORDINATES]:0.0,0.0,0.0 ", 2);
	ft_putstr_fd("[VERTEX]:0.0,0.0,0.0 [RGB]:0-255,0-255,0-255 \n", 2);
	return (PLAN_FORMAT_ERROR);
}

int	cylinder_format_error(char *str)
{
	ft_putstr_fd("File format error: \n", 2);
	ft_putstr_fd("Yours: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	ft_putstr_fd("Expected: [ID]:pl [COORDINATES]:0.0,0.0,0.0 ", 2);
	ft_putstr_fd("[VERTEX]:0.0,0.0,0.0 [DIAMETER]:0.0 [HEIGHT]0.0 ", 2);
	ft_putstr_fd("[RGB]:0-255,0-255,0-255 \n", 2);
	return (CYLINDER_FORMAT_ERROR);
}

int	invalid_type_error(char *str)
{
	ft_putstr_fd("File format error: \n", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	ft_putstr_fd("Invalid type error: Available types are: A C L sp pl cy\n", 2);
	return (INVALID_TYPE_ERROR);
}

int	error(int errnum, char *str)
{
	ft_putstr_fd("Error\n", 2);
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
	if (errnum == PLAN_FORMAT_ERROR)
		return (plan_format_error(str));
	if (errnum == CYLINDER_FORMAT_ERROR)
		return (cylinder_format_error(str));
	if (errnum == INVALID_TYPE_ERROR)
		return (invalid_type_error(str));
	return (0);
}
