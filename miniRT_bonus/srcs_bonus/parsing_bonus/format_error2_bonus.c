#include "miniRT_bonus.h"

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
		ft_putstr_fd("[BUMP_MAP] \"filename_normal_map.xpm\"  "
			" (bump_map optional)   ", 2);
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
	ft_putstr_fd("Invalid type error: "
		"Available types are: A C L sp pl cy\n\n", 2);
	return (INVALID_TYPE_ERROR);
}
