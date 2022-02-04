#include "miniRT.h"

// void	detect_hit_object(t_ray *ray, t_obj *obj, _Bool *hit_obj, double *dist_min, t_intersection *inter_min)
// {
// 	t_intersection	intersection;
	
// 	if (obj->type == SPHERE && hit_sphere(ray, obj, &intersection.intersection, &intersection.normal))
// 	{
// 		*hit_obj = TRUE;
// 		if (*dist_min > ray->closest_hit)
// 		{
// 			*dist_min = ray->closest_hit;
// 			inter_min->intersection = intersection.intersection;
// 			inter_min->normal = intersection.normal;
// 		}
// 	}
// 	else if (obj->type == PLAN && hit_plan(ray, obj, &intersection.intersection, &intersection.normal))
// 	{
// 		*hit_obj = TRUE;
// 		// *color = create_trgb(80, 255, 0, 0);
// 	}
// }

// _Bool	detect_intersection(t_ray *ray, t_obj *obj, int *color, t_data *data)
// {
// 	_Bool			hit_obj;
// 	double			dist_min;
// 	t_intersection	inter_min;

// 	hit_obj = FALSE;
// 	dist_min = 1E99;
// 	while (obj)
// 	{
// 		detect_hit_object(ray, obj, &hit_obj, &dist_min, &inter_min);
// 		obj = obj->next;
// 	}
// 	get_color_pixel(data->scene, inter_min.intersection, inter_min.normal, color);
// 	return (hit_obj);
// }

_Bool	trace_shadow_ray(t_ray *shadow_ray, t_obj *obj)
{
	_Bool	hit_obj;
	double	dist_min;
	t_vec3	intersection;
	t_vec3	normal;

	hit_obj = FALSE;
	dist_min = 1E99;
	while (obj && hit_obj == FALSE)
	{
		if (obj->type == SPHERE && hit_sphere(shadow_ray, obj, &intersection, &normal))
		{
			hit_obj = TRUE;
			if (dist_min > shadow_ray->closest_hit)
			{
				dist_min = shadow_ray->closest_hit;
			}
		}
		else if (obj->type == CYLINDER && hit_cylinder(*shadow_ray, obj, &intersection, &normal)) {
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

_Bool	in_shadow(t_obj *obj, t_vec3 intersection, t_diffuse_light *light, t_vec3 normal)
{
	t_ray	shadow_ray;

	(void)obj;
	//shadow_ray.origin = add_vec3_and_const(intersection, 0.0001);
	shadow_ray.origin = add_vec3(intersection, mul_vec3_and_const(normal, 0.001));
	shadow_ray.dir = sub_vec3(*light->coord, shadow_ray.origin);
	normalize_vec3(&shadow_ray.dir);
	if (trace_shadow_ray(&shadow_ray, obj) == TRUE)
		return (TRUE);
	return (FALSE);
}

_Bool	detect_intersection(t_ray *ray, t_obj *obj, long unsigned int *color, t_data *data)
{
	int i;

	i = 0;
	/*
	_Bool	hit_obj;
	t_vec3	intersection_min;
	t_vec3	normal_min;
	double	dist_min;
	t_vec3	intersection;
	t_vec3	normal;
	t_obj	*tmp;
	double	pixel_shadow = 1;

	tmp = obj;
	(void)color;
	(void)data;
	hit_obj = FALSE;
	dist_min = 1E99;
	while (tmp)
	{
		if (tmp->type == SPHERE && hit_sphere(ray, tmp, &intersection, &normal))
		{
			hit_obj = TRUE;
			if (dist_min > ray->closest_hit)
			{
				dist_min = ray->closest_hit;
				intersection_min = intersection;
				normal_min = normal;
			}
		}
		else if (tmp->type == CYLINDER && hit_cylinder(*ray, tmp, &intersection, &normal))
		{
			hit_obj = TRUE;
			if (dist_min > ray->closest_hit)
			{
				dist_min = ray->closest_hit;
				intersection_min = intersection;
				normal_min = normal;
			}
		}
		else if (tmp->type == PLAN && hit_plan(ray, tmp, &intersection, &normal))
		{
			hit_obj = TRUE;
			// *color = create_trgb(80, 255, 0, 0);
		}
		tmp = tmp->next;
	}
	if (in_shadow(obj, intersection_min, data->scene->diffuse_light, normal_min) == TRUE)
		pixel_shadow = 0.3;
	 */
	//normalize_vec3(data->scene->diffuse_light->coord);
	//while (i++ < 3)
	*color = get_color_pixel(obj, data->scene, ray,  color, 1, 4);
	return (*color);
}


void	run_raytracing(t_mlx *mlx, t_scene *scene, t_data *data)
{
	int			x;
	int			y;
	long unsigned int			color;
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
			if (!detect_intersection(&cam_ray, data->obj, &color, data))
				color = create_trgb(10, 0, 0, 0);
			draw_pixel(mlx->image, x, y, color);
		}
	}
	printf("Render complete\n");
	mlx_put_image_to_window(mlx->ptr, mlx->window, mlx->image->img_ptr, 0, 0);
}
