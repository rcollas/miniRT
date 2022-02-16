#include "miniRT.h"

_Bool	trace_shadow_ray(t_ray *shadow_ray, t_obj *obj, t_diffuse_light *light, t_obj *hit_obj_ref)
{
	t_hit	hit;
	double	light_dist;
	double	dist_min;

	hit.dist = 1E99;
	dist_min = 1E99;
	light_dist = get_norm_vec3(sub_vec3(*light->coord, shadow_ray->origin));
	while (obj)
	{
		if (obj != hit_obj_ref && obj->hit_object(shadow_ray, obj, &hit) && hit.dist < light_dist)
			return (TRUE);
		obj = obj->next;
	}
	return (FALSE);
}

_Bool	is_in_shadow(t_obj *obj, t_ray ray, t_diffuse_light *light, t_obj *hit_obj)
{
	t_ray	shadow_ray;

	shadow_ray.origin = add_vec3(ray.origin, mul_vec3_and_const(ray.dir, 1e-4));
	shadow_ray.dir = sub_vec3(*light->coord, shadow_ray.origin);
	normalize_vec3(&shadow_ray.dir);
	if (trace_shadow_ray(&shadow_ray, obj, light, hit_obj))
		return (TRUE);
	return (FALSE);
}

void	detect_intersection(t_ray *cam_ray, t_obj *obj, unsigned long *color, t_data *data)
{
	int				i;
	unsigned long	nb_of_rays;

	*color = 0;
	nb_of_rays = 3;
	i = nb_of_rays;
	update_camera_ray(cam_ray, data);
	while (i--)
		*color += (get_color_pixel(obj, data->scene, cam_ray, 4) / nb_of_rays);
}

void	run_raytracing(t_mlx *mlx, t_scene *scene, t_data *data, _Bool path_tracing)
{
	unsigned long	pixel_color;
	t_ray			cam_ray;

	init_image(mlx, data);
	init_camera_ray(&cam_ray, data);
	data->cam_to_world_matrix = built_cam_to_word_matrix(scene->camera);
	data->pixel_y = -1;
	while (++data->pixel_y < HEIGHT)
	{
		data->pixel_x = -1;
		while (++data->pixel_x < WIDTH)
		{
			if (path_tracing)
			detect_intersection(&cam_ray, data->obj, &pixel_color, data);
			else if (!prev_detect_intersection(cam_ray, data->obj, &pixel_color, data))
				pixel_color = create_trgb(0, 0, 0);
			draw_pixel(mlx->image, pixel_color, data);
		}
	}
	printf("Render complete\n");
	mlx_put_image_to_window(mlx->ptr, mlx->window, mlx->image->img_ptr, 0, 0);
}
