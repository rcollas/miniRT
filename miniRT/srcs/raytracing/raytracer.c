#include "miniRT.h"

void	init_camera_ray(t_ray *cam_ray, t_scene *scene)
{
	// printf("fov = %f | tan(fov / 2) = %f\n", scene->camera->fov, tan(scene->camera->fov / 2));
	copy_vec3(&cam_ray->origin, scene->camera->origin);
	cam_ray->dir.z = 0;
	cam_ray->dir.x = 0;
	cam_ray->dir.y = 0;
}

void	update_camera_ray(t_ray *cam_ray, t_scene *scene, int y, int x)
{
	(void)scene;
	cam_ray->dir.z = -1 * (WIDTH / (2 * tan(scene->camera->fov / 2)));
	cam_ray->dir.y = y - HEIGHT / 2;
	cam_ray->dir.x = x - WIDTH / 2;
	normalize_vec3(&cam_ray->dir);
}

void	get_color(t_scene *scene, t_vec3 intersection, t_vec3 normal, int *color)
{
	t_vec3		light_vector;
	t_vec3		normalized_light_vector;
	double		intensity;

	light_vector = sub_vec3(*scene->diffuse_light->coord, intersection);
	normalized_light_vector = get_normalized_vec3(light_vector);
	intensity = 1000 * dot_product_vec3(normalized_light_vector, normal);
	intensity /= get_norm2_vec3(light_vector);
	// printf("intensity = %f\n", intensity);
	clamp_intensity(&intensity);
	*color = create_trgb(98, 136 * intensity, 32 * intensity, 250 * intensity);
}

_Bool	detect_intersection(t_ray ray, t_obj *obj, int *color, t_data *data)
{
	_Bool	hit_obj;
	t_vec3	intersection;
	t_vec3	normal;

	(void)color;
	hit_obj = FALSE;
	while (obj)
	{
		if (obj->type == SPHERE && hit_sphere(ray, obj, &intersection, &normal))
			hit_obj = TRUE;
		// else if (obj->type == PLAN && hit_plan(ray, obj, &intersection, &normal))
		// {
		// 	hit_obj = TRUE;
		// }
		obj = obj->next;
	}
	get_color(data->scene, intersection, normal, color);
	return (hit_obj);
}

void	run_raytracing(t_mlx *mlx, t_scene *scene, t_data *data)
{
	int			x;
	int			y;
	int			color;
	t_ray		cam_ray;
	t_matrix4	cam_to_world_matrix;

	y = -1;
	cam_to_world_matrix = built_cam_to_word_matrix(data->scene->camera);
	init_image(mlx, data);
	init_camera_ray(&cam_ray, scene);
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			update_camera_ray(&cam_ray, scene, y, x);
			// printf("ray.dir = %f, %f, %f\n", cam_ray.dir->x, cam_ray.dir->y, cam_ray.dir->z);
			if (!detect_intersection(cam_ray, data->obj, &color, data))
				color = create_trgb(10, 0, 0, 0);
			draw_pixel(mlx->image, x, y, color);
		}
	}
	mlx_put_image_to_window(mlx->ptr, mlx->window, mlx->image->img_ptr, 0, 0);
}
