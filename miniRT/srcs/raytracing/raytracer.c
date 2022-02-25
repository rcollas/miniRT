#include "miniRT.h"

_Bool	check_hit_object(
	t_ray *ray, t_obj *obj, t_ray *hit_min)
{
	t_ray	hit;

	if (obj->hit_object(ray, obj, &hit))
	{
		if (hit_min->dist > hit.dist)
		{
			hit_min->dist = hit.dist;
			hit_min->shine_factor = obj->shine_factor;
			copy_vec3(&hit_min->origin, hit.origin);
			copy_vec3(&hit_min->dir, hit.dir);
			copy_vec3(&hit_min->color, *obj->color);
		}
		return (TRUE);
	}
	return (FALSE);
}

void	init_var_hit(_Bool *hit_obj, t_ray *hit, t_vec3 *color)
{
	*hit_obj = FALSE;
	hit->dist = 1E99;
	hit->pixel_shadow = 1;
	hit->obj_ref = -1;
	*color = create_vec3(0, 0, 0);
}

void	detect_intersection(
	t_ray ray, t_obj *obj, t_vec3 *color, t_data *data)
{
	_Bool	hit_obj;
	t_ray	hit;
	t_vec3	rgb;
	int		i;

	i = 0;
	init_var_hit(&hit_obj, &hit, &rgb);
	update_camera_ray(&ray, data);
	while (i < data->obj_nb)
	{
		if (check_hit_object(&ray, &obj[i], &hit))
		{
			hit_obj = TRUE;
			hit.obj_ref = i;
		}
		i++;
	}
	if (hit_obj)
	{
		if (is_in_shadow(obj, hit, data->scene->diffuse_light))
			hit.pixel_shadow = 0.5;
		rgb = get_light(data, hit, ray);
	}
	*color = rgb;
}

/*
t_vec3	get_color_components(unsigned long color)
{
	t_vec3	color_vec;

	color_vec.coord[R] = (double)(color & 9);
	color_vec.coord[G] = (double)(color & 6);
	color_vec.coord[B] = (double)(color & 3);
	if (color_vec.coord[R] || color_vec.coord[G] || color_vec.coord[B])
	{
		printf("color R = %f\n", color_vec.coord[R]);
		printf("color G = %f\n", color_vec.coord[G]);
		printf("color B = %f\n", color_vec.coord[B]);
	}
	return (color_vec);
}
 */

void	run_raytracing(
	t_mlx *mlx, t_scene *scene, t_data *data, _Bool path_tracing)
{
	unsigned long 	pixel_color;
	t_ray			cam_ray;
	double			start;
	t_vec3 			*color;
	t_vec3 			tmp;
	int 			j;

	init_image(mlx, data);
	init_camera_ray(&cam_ray, data);
	data->cam_to_world_matrix = built_cam_to_world_matrix(scene->camera);
	data->pixel_y = -1;
	start = get_time();
	color = malloc(sizeof(t_vec3) * HEIGHT * 2 * WIDTH * 2 + 1);
	j = 0;
	(void)path_tracing;
	while (++data->pixel_y < HEIGHT * 4)
	{
		data->pixel_x = -1;
		while (++data->pixel_x < WIDTH * 4)
		{
			//if (path_tracing)
			//	run_path_tracing(&cam_ray, data->obj, &color[j], data);
			//else
				detect_intersection(cam_ray, data->obj, &color[j], data);
			//draw_pixel(mlx->image, pixel_color, data);
			j++;
		}
	}
	data->pixel_y = -1;
	j = 0;
	while (++data->pixel_y < HEIGHT)
	{
		data->pixel_x = -1;
		while (++data->pixel_x < WIDTH)
		{
			//if (j < HEIGHT * WIDTH * 4 - 2)
			//{
				tmp = add_vec3(color[j], color[j + 1]);
				tmp = add_vec3(color[j], color[j + 1]);
				tmp = div_vec3_and_const(tmp, 2);
				pixel_color = create_rgb_struct(&tmp);
				draw_pixel(mlx->image, pixel_color, data);
			//}
			j += 2;
		}
	}
	printf("Render time: %fs\n", (get_time() - start) / 1000);
	display_cam_param(data->scene->camera);
	mlx_put_image_to_window(mlx->ptr, mlx->window, mlx->image->img_ptr, 0, 0);
}
