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

void	draw_pixel(t_mlx *mlx, int x, int y, int color)
{
	char			*dest;

	dest = mlx->addr + (y * mlx->size_line + x * mlx->bpp);
	*(unsigned int *)dest = color;
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

void	print_window(t_mlx *mlx, t_scene *scene)
{
	int		x;
	int		y;
	int		color;
	t_ray	ray[1];

	y = -1;
	scene->camera->fov = scene->camera->fov * M_PI / 180;
	copy_coord(ray->origin, scene->camera->coord);
	while (++y < HEIGHT)
	{
		ray->dir->y = y - HEIGHT / 2;
		x = -1;
		while (++x < WIDTH)
		{
			ray->dir->x = x - WIDTH / 2;
			ray->dir->z = -1 * (WIDTH / (2 * tan(scene->camera->fov / 2)));
			color = create_trgb(80, 255, 0, 0);
			draw_pixel(mlx, x, y, color);
		}
	}
	mlx_put_image_to_window(mlx->ptr, mlx->window, mlx->image, 0, 0);
}

int	main(int argc, char **argv)
{
	t_parsing	parsing_var[1];
	t_data		data[1];

	if (parsing(argv, argc, parsing_var) == FAIL)
		exit(EXIT_FAILURE);
	init_data(parsing_var, data);
	print_window(data->mlx, parsing_var->scene);
	events_loop(data);
	print_list(data->obj);
	free_list(data->obj);
	return (0);
}
