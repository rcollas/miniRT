#include "miniRT.h"

void	exit_error(t_data *data)
{
	clean_data(data);
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
	*(unsigned int *)dest = color;
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

void	copy_coord(t_coord *dest, t_coord *src)
{
	dest->x = src->x;
	dest->y = src->y;
	dest->z = src->z;
}

void	copy_vec3(t_vec3 *dest, t_vec3 *src)
{
	dest->x = src->x;
	dest->y = src->y;
	dest->z = src->z;
}

void	print_window(t_mlx *mlx, t_scene *scene, t_data *data)
{
	int		x;
	int		y;
	int		color;
	t_ray	ray[1];

	y = -1;
	scene->camera->fov = scene->camera->fov * M_PI / 180;
	copy_coord(ray->origin, scene->camera->coord);
	init_image(mlx, data);
	while (++y < HEIGHT)
	{
		ray->dir->y = y - HEIGHT / 2;
		x = -1;
		while (++x < WIDTH)
		{
			ray->dir->x = x - WIDTH / 2;
			ray->dir->z = -1 * (WIDTH / (2 * tan(scene->camera->fov / 2)));
			color = create_trgb(80, 255, 0, 0);
			draw_pixel(mlx->image, x, y, color);
		}
	}
	mlx_put_image_to_window(mlx->ptr, mlx->window, mlx->image->img_ptr, 0, 0);
}

int	main(int argc, char **argv)
{
	t_parsing	parsing_var[1];
	t_data		data[1];

	if (parsing(argv, argc, parsing_var) == FAIL)
		return (EXIT_FAILURE);
	init_data(parsing_var, data);
	print_window(data->mlx, data->scene, data);
	events_loop(data);
	print_list(data->obj);
	clean_data(data);
	return (0);
}
