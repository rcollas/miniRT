#include "miniRT_bonus.h"

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
