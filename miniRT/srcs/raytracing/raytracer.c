#include "miniRT.h"

void	init_hit_object(t_op *hit_object[2])
{
	hit_object[SPHERE] = hit_sphere;
	hit_object[PLAN] = hit_plan;
}

_Bool	check_hit_object(t_ray *ray, t_obj *obj, t_hit *hit_min)
{
	t_hit	hit;
	t_op	*hit_object[2];
	
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

_Bool	detect_intersection(t_ray ray, t_obj *obj, int *color, t_data *data)
{
	_Bool	hit_obj;
	t_hit	hit_min;

	hit_obj = FALSE;
	hit_min.dist = 1E99;
	update_camera_ray(&ray, data);
	while (obj)
	{
		if (check_hit_object(&ray, obj, &hit_min))
			hit_obj = TRUE;
		obj = obj->next;
	}
	get_color_pixel(data->scene, hit_min, color);
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
	mlx_put_image_to_window(mlx->ptr, mlx->window, mlx->image->img_ptr, 0, 0);
}
