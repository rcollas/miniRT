#include "miniRT.h"

void	init_hit_object(t_op *hit_object[2])
{
	hit_object[SPHERE] = hit_sphere;
	hit_object[PLAN] = hit_plan;
	hit_object[CYLINDER] = hit_cylinder;
}

_Bool	check_hit_object(t_ray *ray, t_obj *obj, t_hit *hit_min)
{
	t_hit	hit;
	t_op	*hit_object[3];

	init_hit_object(hit_object);
	if (hit_object[obj->type](ray, obj, &hit))
	{
		if (hit_min->dist > ray->closest_hit)
		{
			hit_min->dist = ray->closest_hit;
			hit_min->intersection = hit.intersection;
			hit_min->normal = hit.normal;
			hit_min->color = *obj->color;
		}
		return (TRUE);
	}
	// *color = create_trgb(80, 255, 0, 0);
	return (FALSE);
}

_Bool	trace_shadow_ray(t_ray *shadow_ray, t_obj *obj)
{
	_Bool	hit_obj;
	double	dist_min;
	t_hit	hit;

	hit_obj = FALSE;
	dist_min = 1E99;
	while (obj)
	{
		if (obj->type == SPHERE && hit_sphere(shadow_ray, obj, &hit))
		{
			hit_obj = TRUE;
			if (dist_min > shadow_ray->closest_hit)
			{
				dist_min = shadow_ray->closest_hit;
			}
		}
		else if (obj->type == CYLINDER && hit_cylinder(shadow_ray, obj, &hit))
		{
			hit_obj = TRUE;
			if (dist_min > shadow_ray->closest_hit)
			{
				dist_min = shadow_ray->closest_hit;
			}
		}
			obj = obj->next;
	}
	/*
	if (hit_obj)
		printf("TRUE\n");
	else
		printf("FALSE\n");
	 */
	return (hit_obj);
}

_Bool	in_shadow(t_obj *obj, t_vec3 intersection, t_diffuse_light *light)
{
	t_ray	shadow_ray;

	(void)obj;
	shadow_ray.origin = add_vec3_and_const(intersection, 0.0000001);
	shadow_ray.dir = sub_vec3(*light->coord, shadow_ray.origin);
	normalize_vec3(&shadow_ray.dir);
	if (trace_shadow_ray(&shadow_ray, obj) == TRUE)
		return (TRUE);
	return (FALSE);
}

_Bool	detect_intersection(t_ray ray, t_obj *obj, int *color, t_data *data)
{
	_Bool	hit_obj;
	t_hit	hit_min;
	t_obj	*tmp;
	double	pixel_shadow;

	pixel_shadow = 1;
	tmp = obj;
	hit_obj = FALSE;
	hit_min.dist = 1E99;
	update_camera_ray(&ray, data);
	while (tmp)
	{
		if (check_hit_object(&ray, tmp, &hit_min))
			hit_obj = TRUE;
		tmp = tmp->next;
	}
	if (in_shadow(tmp, hit_min.intersection, data->scene->diffuse_light) == TRUE)
		pixel_shadow = 0.3;
	//normalize_vec3(data->scene->diffuse_light->coord);
	get_color_pixel(data->scene, hit_min, color, pixel_shadow);
	return (hit_obj);
}


void	run_raytracing(t_mlx *mlx, t_scene *scene, t_data *data)
{
	int		pixel_color;
	t_ray	cam_ray;

	init_image(mlx, data);
	init_camera_ray(&cam_ray, scene);
	data->cam_to_world_matrix = built_cam_to_word_matrix(data->scene->camera);
	data->pixel_y = -1;
	while (++data->pixel_y < HEIGHT)
	{
		data->pixel_x = -1;
		while (++data->pixel_x < WIDTH)
		{
			if (!detect_intersection(cam_ray, data->obj, &pixel_color, data))
				pixel_color = create_trgb(10, 0, 0, 0);
			draw_pixel(mlx->image, data->pixel_x, data->pixel_y, pixel_color);
		}
	}
	printf("Render complete\n");
	mlx_put_image_to_window(mlx->ptr, mlx->window, mlx->image->img_ptr, 0, 0);
}
