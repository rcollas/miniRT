#include "miniRT.h"

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

void	init_camera_ray(t_ray *cam_ray, t_scene *scene)
{
	// printf("fov = %f | tan(fov / 2) = %f\n", scene->camera->fov, tan(scene->camera->fov / 2));
	copy_vec3(cam_ray->origin, scene->camera->coord);
	cam_ray->dir->z = 0;
	cam_ray->dir->x = 0;
	cam_ray->dir->y = 0;
}

void	update_camera_ray(t_ray *cam_ray, t_scene *scene, int y, int x)
{
	(void)scene;
	cam_ray->dir->z = -1 * (WIDTH / (2 * tan(scene->camera->fov / 2)));
	cam_ray->dir->y = y - HEIGHT / 2;
	cam_ray->dir->x = x - WIDTH / 2;
	normalize_vec3(cam_ray->dir);
}

_Bool	resolve_quadratic_equation(double a, double b, double c)
{
	double	delta;
	double	ret[2];
	double	closest_hit;

	delta = b * b - (4 * a * c);
	if (delta < 0)
		return (0);
	ret[0] = (-b - (sqrt(delta))) / (2 * a);
	ret[1] = (-b + (sqrt(delta))) / (2 * a);
	// printf("ret = %f\n", ret[1]);
	if (ret[1] < 0)
		return (FALSE);
	if (ret[0] > 0)
		closest_hit = ret[0];
	else
		closest_hit = ret[1];
	return (TRUE);
}

_Bool	hit_sphere(t_ray ray, t_obj *obj)
{
	double 	a;
	double	b;
	double	c;
	double	radius;

	radius = obj->diameter / 2;
	a = 1;
	b = 2 * dot_product_vec3(*ray.dir, sub_vec3(ray.origin, obj->coord));
	c = get_norm2_vec3(sub_vec3(ray.origin, obj->coord)) - radius * radius;
	if (resolve_quadratic_equation(a, b, c))
		return (TRUE);
	return (FALSE);
}

_Bool	check_intersection(t_ray ray, t_obj *obj)
{
	_Bool	hit_obj;

	hit_obj = FALSE;
	while (obj)
	{
		if (obj->type == SPHERE && hit_sphere(ray, obj))
			hit_obj = TRUE;
		obj = obj->next;
	}
	return (hit_obj);
}

void	run_raytracing(t_mlx *mlx, t_scene *scene, t_data *data)
{
	int		x;
	int		y;
	int		color;
	t_ray	cam_ray;

	y = -1;
	init_image(mlx, data);
	init_camera_ray(&cam_ray, scene);
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			update_camera_ray(&cam_ray, scene, y, x);
			// printf("ray.dir = %f, %f, %f\n", cam_ray.dir->x, cam_ray.dir->y, cam_ray.dir->z);
			color = create_trgb(98, data->obj->rgb->r, data->obj->rgb->g, data->obj->rgb->b);
			if (check_intersection(cam_ray, data->obj))
				draw_pixel(mlx->image, x, y, color);
		}
	}
	mlx_put_image_to_window(mlx->ptr, mlx->window, mlx->image->img_ptr, 0, 0);
}
