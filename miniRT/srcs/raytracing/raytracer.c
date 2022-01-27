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

_Bool	detect_intersection(t_ray *ray, t_obj *obj, int *color, t_data *data)
{
	_Bool	hit_obj;
	t_vec3	intersection_min;
	t_vec3	normal_min;
	double	dist_min;
	t_vec3	intersection;
	t_vec3	normal;

	hit_obj = FALSE;
	dist_min = 1E99;
	while (obj)
	{
		if (obj->type == SPHERE && hit_sphere(ray, obj, &intersection, &normal))
		{
			hit_obj = TRUE;
			if (dist_min > ray->closest_hit)
			{
				dist_min = ray->closest_hit;
				intersection_min = intersection;
				normal_min = normal;
			}
		}
		else if (obj->type == PLAN && hit_plan(ray, obj, &intersection, &normal))
		{
			hit_obj = TRUE;
			// *color = create_trgb(80, 255, 0, 0);
		}
		obj = obj->next;
	}
	get_color_pixel(data->scene, intersection_min, normal_min, color);
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
			if (!detect_intersection(&cam_ray, data->obj, &color, data))
				color = create_trgb(10, 0, 0, 0);
			draw_pixel(mlx->image, x, y, color);
		}
	}
	mlx_put_image_to_window(mlx->ptr, mlx->window, mlx->image->img_ptr, 0, 0);
}
