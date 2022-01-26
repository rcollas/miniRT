#include "miniRT.h"

void	exit_error(t_data *data)
{
	clean_data(data);
	exit(EXIT_FAILURE);
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

int	main(int argc, char **argv)
{
	t_parsing	parsing_var[1];
	t_data		data[1];

	if (parsing(argv, argc, parsing_var) == FAIL)
		return (EXIT_FAILURE);
	init_data(parsing_var, data);
	run_raytracing(data->mlx, data->scene, data);
	events_loop(data);
	print_list(data->obj);
	clean_data(data);
	return (0);
}
