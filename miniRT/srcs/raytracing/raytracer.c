#include "miniRT.h"

// _Bool	check_hit_object(t_ray *ray, t_obj *obj, t_hit *hit_min)
// {
// 	t_hit	hit;

// 	if (obj->hit_object(ray, obj, &hit)(ray, obj, &hit))
// 	{
// 		if (hit_min->dist > ray->closest_hit)
// 		{
// 			hit_min->dist = ray->closest_hit;
// 			copy_vec3(&hit_min->intersection, hit.intersection);
// 			copy_vec3(&hit_min->normal, hit.normal);
// 			copy_vec3(&hit_min->color, *obj->color);
// 		}
// 		return (TRUE);
// 	}
// 	return (FALSE);
// }

_Bool	trace_shadow_ray(t_ray *shadow_ray, t_obj *obj, t_diffuse_light *light)
{
	_Bool	hit_obj;
	t_hit	hit;
	double	light_dist;
	double	dist_min;

	hit_obj = FALSE;
	hit.dist = 1E99;
	dist_min = 1E99;
	light_dist = get_norm_vec3(sub_vec3(*light->coord, shadow_ray->origin));
	while (obj)
	{
		if (obj->hit_object(shadow_ray, obj, &hit) && hit.dist < light_dist)
		{
			hit_obj = TRUE;
			if (dist_min > shadow_ray->closest_hit)
				dist_min = shadow_ray->closest_hit;
		}
		obj = obj->next;
	}
	return (hit_obj);
}

_Bool	is_in_shadow(t_obj *obj, t_ray ray, t_diffuse_light *light)
{
	t_ray	shadow_ray;

	shadow_ray.origin = add_vec3(ray.origin, mul_vec3_and_const(ray.dir, 1e-4));
	shadow_ray.dir = sub_vec3(*light->coord, shadow_ray.origin);
	normalize_vec3(&shadow_ray.dir);
	if (trace_shadow_ray(&shadow_ray, obj, light))
		return (TRUE);
	return (FALSE);
}

// _Bool	detect_intersection(t_ray ray, t_obj *obj, int *color, t_data *data)
// {
// 	_Bool	hit_obj;
// 	t_hit	hit_min;
// 	t_obj	*current_obj;
// 	t_obj 	*no_check;

// 	hit_min.pixel_shadow = 1;
// 	hit_obj = FALSE;
// 	hit_min.dist = 1E99;
// 	update_camera_ray(&ray, data);
// 	current_obj = obj;
// 	while (current_obj)
// 	{
// 		if (check_hit_object(&ray, current_obj, &hit_min))
// 		{
// 			no_check = current_obj;
// 			hit_obj = TRUE;
// 		}
// 		current_obj = current_obj->next;
// 	}
// 	if (hit_obj)
// 	{
// 		if (is_in_shadow(obj, hit_min, data->scene->diffuse_light))
// 			hit_min.pixel_shadow = 0.3;
// 		get_color_pixel(data->scene, hit_min, ray, color);
// 	}
// 	return (hit_obj);
// }

_Bool	detect_intersection(t_ray *cam_ray, t_obj *obj, long unsigned int *color, t_data *data)
{
	int i;

	i = 0;
	update_camera_ray(cam_ray, data);
	*color = get_color_pixel(obj, data->scene, cam_ray,  color, 1, 4);
	return (*color);
}

void	run_raytracing(t_mlx *mlx, t_scene *scene, t_data *data)
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
			if (!detect_intersection(&cam_ray, data->obj, &pixel_color, data))
				pixel_color = create_trgb(10, 0, 0, 0);
			draw_pixel(mlx->image, pixel_color, data);
		}
	}
	printf("Render complete\n");
	mlx_put_image_to_window(mlx->ptr, mlx->window, mlx->image->img_ptr, 0, 0);
}
