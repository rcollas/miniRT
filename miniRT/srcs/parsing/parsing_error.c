#include "miniRT.h"

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

int	parsing_error(int errnum, char *str)
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

int	strdup_error(void)
{
	ft_putstr_fd("Critical error: Strdup failed\n", 2);
	return (STRDUP_ERROR);
}

void	error_coordinates(void)
{
	ft_putstr_fd("[COORDINATES] 0.0,0.0,0.0   ", 2);
}

void	error_diameter(void)
{
	ft_putstr_fd("[DIAMETER] 0.0   ", 2);
}

void	error_height(void)
{
	ft_putstr_fd("[HEIGHT] 0.0   ", 2);
}

void	error_rgb(void)
{
	ft_putstr_fd("[RGB] 0-255,0-255,0-255   ", 2);
}

void	error_vertex(void)
{
	ft_putstr_fd("[VERTEX] 0.0,0.0,0.0   ", 2);
}

void	error_intensity(void)
{
	ft_putstr_fd("[INTENSITY] 0.0-1.0   ", 2);
}

void	format_bonus(_Bool has_texture)
{
	ft_putstr_fd("\n\t+   ", 2);
	error_rgb();
	ft_putstr_fd("\n       or   ", 2);
	error_rgb();
	error_rgb();
	ft_putstr_fd("(checker)", 2);
	if (has_texture)
	{
		ft_putstr_fd("\n       or   ", 2);
		ft_putstr_fd("[TEXTURE] \"filename.xpm\"  ", 2);
		ft_putstr_fd("[BUMP_MAP] \"filename_normal_map.xpm\"   (bump_map optional)   ", 2);
	}
}

void	file_format_error(void)
{
	ft_putstr_fd("File format error\n\n", 2);
	ft_putstr_fd("\033[1;31m    Yours:   ", 2);
}

int	ambient_light_format_error(char *str)
{
	file_format_error();
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n\033[38;5;121m Expected:  [ID] A   ", 2);
	error_intensity();
	error_rgb();
	ft_putstr_fd("\033[0m\n\n", 2);
	return (AMBIENT_LIGHT_FORMAT_ERROR);
}

int	camera_format_error(char *str)
{
	file_format_error();
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n\033[38;5;121m Expected:  [ID] C   ", 2);
	error_coordinates();
	error_vertex();
	ft_putstr_fd("[FOV] 0-180   ", 2);
	ft_putstr_fd("\033[0m\n\n", 2);
	return (CAMERA_FORMAT_ERROR);
}

int	diffuse_light_format_error(char *str)
{
	file_format_error();
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n\033[38;5;121m Expected:  [ID] L   ", 2);
	error_coordinates();
	error_intensity();
	if (BONUS)
		error_rgb();
	ft_putstr_fd("\033[0m\n\n", 2);
	return (DIFFUSE_LIGHT_FORMAT_ERROR);
}

int	sphere_format_error(char *str)
{
	file_format_error();
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n\033[38;5;121m Expected:  [ID] sp   ", 2);
	error_coordinates();
	error_diameter();
	if (BONUS)
		format_bonus(HAS_TEXTURE);
	else
		error_rgb();
	ft_putstr_fd("\033[0m\n\n", 2);
	return (SPHERE_FORMAT_ERROR);
}

int	plane_format_error(char *str)
{
	file_format_error();
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n\033[38;5;121m Expected:  [ID] pl   ", 2);
	error_coordinates();
	error_vertex();
	if (BONUS)
		format_bonus(NO_TEXTURE);
	else
		error_rgb();
	ft_putstr_fd("\033[0m\n\n", 2);
	return (PLANE_FORMAT_ERROR);
}

int	cylinder_format_error(char *str)
{
	file_format_error();
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n\033[38;5;121m Expected:  [ID] cy   ", 2);
	error_coordinates();
	error_vertex();
	error_diameter();
	error_height();
	if (BONUS)
		format_bonus(HAS_TEXTURE);
	else
		error_rgb();
	ft_putstr_fd("\033[0m\n\n", 2);
	return (CYLINDER_FORMAT_ERROR);
}

int	cone_format_error(char *str)
{
	file_format_error();
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n\033[38;5;121m Expected:  [ID] co   ", 2);
	error_coordinates();
	error_vertex();
	error_diameter();
	error_height();
	if (BONUS)
		format_bonus(NO_TEXTURE);
	else
		error_rgb();
	ft_putstr_fd("\033[0m\n\n", 2);
	return (CONE_FORMAT_ERROR);
}

int	square_format_error(char *str)
{
	file_format_error();
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n\033[38;5;121m Expected:  [ID] sq   ", 2);
	error_coordinates();
	error_vertex();
	error_height();
	if (BONUS)
		format_bonus(HAS_TEXTURE);
	else
		error_rgb();
	ft_putstr_fd("\033[0m\n\n", 2);
	return (SQUARE_FORMAT_ERROR);
}

int	disk_format_error(char *str)
{
	file_format_error();
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n\033[38;5;121m Expected:  [ID] di   ", 2);
	error_coordinates();
	error_vertex();
	error_diameter();
	ft_putstr_fd("[INNER_DIAMETER] 0.0   ", 2);
	if (BONUS)
		format_bonus(HAS_TEXTURE);
	else
		error_rgb();
	ft_putstr_fd("\033[0m\n\n", 2);
	return (DISK_FORMAT_ERROR);
}

int	sky_format_error(char *str)
{
	file_format_error();
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n\033[38;5;121m Expected:  [ID] sky   ", 2);
	error_coordinates();
	error_diameter();
	if (BONUS)
		format_bonus(HAS_TEXTURE);
	else
		error_rgb();
	ft_putstr_fd("\033[0m\n\n", 2);
	return (SPHERE_FORMAT_ERROR);
}

int	invalid_type_error(char *str)
{
	ft_putstr_fd("File format error\n\n", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	ft_putstr_fd("Invalid type error: Available types are: A C L sp pl cy\n\n", 2);
	return (INVALID_TYPE_ERROR);
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
	if (errnum == CONE_FORMAT_ERROR)
		return (cone_format_error(str));
	if (errnum == DISK_FORMAT_ERROR)
		return (disk_format_error(str));
	if (errnum == SQUARE_FORMAT_ERROR)
		return (square_format_error(str));
	if (errnum == SKY_FORMAT_ERROR)
		return (sky_format_error(str));
	if (errnum == INVALID_TYPE_ERROR)
		return (invalid_type_error(str));
	return (0);
}
