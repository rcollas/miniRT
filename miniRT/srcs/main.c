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

void	draw_pixel(t_image *image, int x, int y, int color)
{
	char			*dest;

	dest = image->addr + (y * image->line_len + x * image->bpp / 8);
	*(int *)dest = color;
}

void	fill_background(t_mlx *mlx, int color)
{
	int	x;
	int	y;

	y = 1;
	while (++y < HEIGHT - 1)
	{
		x = -1;
		while (++x < WIDTH - 1)
			draw_pixel(mlx->image, x, y, color);
	}
}

void	draw_square(int x, int y, int length, int color, t_mlx *mlx)
{
	int x2;
	int y2;

	y2 = y - length / 2;
	while (y2 < y + length)
	{
		x2 = x - length / 2;
		while (x2 < x + length)
		{
			if (x2 >= 0 && y2 >= 0 && x2 <= WIDTH && y2 <= HEIGHT)
				draw_pixel(mlx->image, x2, y2, color);
			x2++;
		}
		y2++;
	}
}

void	draw_coordinate_system(t_mlx *mlx, int scale, int color)
{
	int	x;
	int	y;

	y = -1;
	while (++y < HEIGHT - 1)
	{
		x = -1;
		while (++x < WIDTH - 1)
		{
			if (!(y % scale && x % scale))
			{
				if (y == HEIGHT / 2 || x == WIDTH / 2)
					draw_square(x, y, 2, color, mlx);
				else
					draw_pixel(mlx->image, x, y, color);
			}
		}
	}
}

void	print_window(t_mlx *mlx)
{
	int	color;

	init_image(mlx);
	color = create_trgb(80, 255, 255, 255);
	fill_background(mlx, color);
	color = create_trgb(80, 0, 0, 0);
	draw_coordinate_system(mlx, 10, color);
	color = create_trgb(80, 0, 0, 255);
	draw_square(250, 100, 50, color, mlx);
	mlx_put_image_to_window(mlx->ptr, mlx->window, mlx->image->img_ptr, 0, 0);
	mlx_string_put(mlx->ptr, mlx->window, WIDTH / 2 - 20, HEIGHT / 2 + 20, create_trgb(0, 0, 0, 0), "0");
}

int	main(int argc, char **argv)
{
	t_mlx		*mlx;
	t_parsing	parsing_var[1];

	if (parsing(argv, argc, parsing_var) == FAIL)
		return (EXIT_FAILURE);
	mlx = setup_mlx();
	print_window(mlx);
	events_loop(mlx);
	//print_list(parsing_var->objs);
	free_list(parsing_var->objs);
	return (0);
}
