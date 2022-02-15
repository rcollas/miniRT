#include "miniRT.h"

_Bool	trace_shadow_ray(t_ray *shadow_ray, t_obj *obj, t_diffuse_light *light, t_obj *hit_obj_ref)
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
		if (obj != hit_obj_ref && obj->hit_object(shadow_ray, obj, &hit) && hit.dist < light_dist)
			return (TRUE);
		obj = obj->next;
	}
	return (hit_obj);
}

_Bool	is_in_shadow(t_obj *obj, t_ray ray, t_diffuse_light *light, t_obj *hit_obj)
{
	t_ray	shadow_ray;

	shadow_ray.origin = add_vec3(ray.origin, mul_vec3_and_const(ray.dir, 1e-2));
	shadow_ray.dir = sub_vec3(*light->coord, shadow_ray.origin);
	//normalize_vec3(&shadow_ray.dir);
	//normalize_vec3(&shadow_ray.origin);
	if (trace_shadow_ray(&shadow_ray, obj, light, hit_obj))
		return (TRUE);
	return (FALSE);
}

void	detect_intersection(t_ray *cam_ray, t_obj *obj, unsigned long *color, t_data *data)
{
	int				i;
	unsigned long	nb_of_rays;
	t_vec3 			rgb;

	*color = 0;
	nb_of_rays = 18;
	i = nb_of_rays;
	update_camera_ray(cam_ray, data);
	// *color = get_color_pixel(obj, data->scene, cam_ray, 1, 4);
	rgb.coord[R] = 0;
	rgb.coord[G] = 0;
	rgb.coord[B] = 0;
	while (i--)
		rgb = add_vec3(rgb, *get_color_pixel(obj, data->scene, cam_ray, 1, 14));
	rgb = div_vec3_and_const(rgb, (double)nb_of_rays);
	*color = create_trgb_struct(90, &rgb);
	// printf("color = %lu\n", *color);
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
			detect_intersection(&cam_ray, data->obj, &pixel_color, data);
			// if (!prev_detect_intersection(cam_ray, data->obj, &pixel_color, data))
			// 	pixel_color = create_trgb(10, 0, 0, 0);
			draw_pixel(mlx->image, pixel_color, data);
		}
	}
	printf("Render complete\n");
	mlx_put_image_to_window(mlx->ptr, mlx->window, mlx->image->img_ptr, 0, 0);
}
