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

void	print_window(t_mlx *mlx, t_scene *scene)
{
	int		x;
	int		y;
	int		color;
	t_ray	ray;

	y = -1;
	scene->camera->fov = scene->camera->fov * M_PI / 180;
	(void)ray;
	// ray.origin = scene->camera->coord;
	while (++y < HEIGHT)
	{
		// ray.dir->y = y - HEIGHT / 2;
		x = -1;
		while (++x < WIDTH)
		{
			// ray.dir->x = x - WIDTH / 2;
			// ray.dir->z = -1 * (WIDTH / (2 * tan(scene->camera->fov / 2)));
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
	print_window(mlx, parsing_var->scene);
	events_loop(mlx);
	print_list(parsing_var->objs);
	free_list(parsing_var->objs);
	return (0);
}
