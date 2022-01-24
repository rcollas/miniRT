#include "miniRT.h"

void	exit_error(t_mlx *mlx)
{
	clean_mlx(mlx);
	exit(EXIT_FAILURE);
}

int	create_trgb(int transparency, int red, int green, int blue)
{
	return (transparency << 24 | red << 16 | green << 8 | blue);
}

void	draw_pixel(t_mlx *mlx, int x, int y, int color)
{
	char			*dest;

	dest = mlx->addr + (y * mlx->size_line + x * mlx->bpp);
	*(unsigned int *)dest = color;
}

void	print_window(t_mlx *mlx)
{
	int	x;
	int	y;
	int	color;

	y = -1;
	while (++y < HEIGHT - 1)
	{
		x = -1;
		while (++x < WIDTH - 1)
		{
			color = create_trgb(80, 255, 0, 0);
			draw_pixel(mlx, x, y, color);
		}
	}
	mlx_put_image_to_window(mlx->ptr, mlx->window, mlx->image, 0, 0);
}

int	main(int argc, char **argv)
{
	t_mlx		*mlx;
	t_parsing	parsing_var[1];

	(void)mlx;
	(void)argc;
	(void)argv;
	if (parsing(argv, argc, parsing_var) == FAIL)
		exit(EXIT_FAILURE);
	mlx = setup_mlx();
	print_window(mlx);
	events_loop(mlx);
	print_list(parsing_var->objs);
	free_list(parsing_var->objs);
	return (0);
}
