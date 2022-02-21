#include "miniRT.h"

t_ray	*get_random_ray(t_ray result)
{
	t_ray		*random_ray;
	double		r1;
	double 		r2;
	t_vec3		random_dir_local;
	t_vec3		random_dir;
	t_vec3		random;
	t_vec3		tangent1;
	t_vec3		tangent2;

	random_ray = ft_calloc(1, sizeof(t_ray));
	srand(ft_rand());
	r1 = frand();
	r2 = frand();
	random_dir_local.coord[X] = cos(2 * M_PI * r1) * sqrt(1 - r2);
	random_dir_local.coord[Y] = sin(2 * M_PI * r1) * sqrt(1 - r2);
	random_dir_local.coord[Z] = sqrt(r2);
	random.coord[X] = frand();
	random.coord[Y] = frand();
	random.coord[Z] = frand();
	tangent1 = cross_vec3(result.dir, random);
	normalize_vec3(&tangent1);
	tangent2 = cross_vec3(tangent1, result.dir);
	random_dir = add_vec3(mul_vec3_and_const(result.dir, random_dir_local.coord[Z]),
						  add_vec3(mul_vec3_and_const(tangent1, random_dir_local.coord[X]),
								   mul_vec3_and_const(tangent2, random_dir_local.coord[Y])));
	random_ray->dir = random_dir;
	random_ray->origin = add_vec3(result.origin, mul_vec3_and_const(result.dir, 0.1));
	normalize_vec3(&random_ray->origin);
	//random_ray->origin = add_vec3(result.origin, result.dir);
	return (random_ray);
}

_Bool	check_all_objects(t_obj *obj, t_ray *ray, t_ray *result, int *hit_obj_ref)
{
	t_hit	hit;
	_Bool	hit_obj;
	double	dist_min;
	int		i;

	dist_min = 1E99;
	hit_obj = FALSE;
	i = 0;
	result->color = create_vec3(0, 0, 0);
	while (i < obj->obj_nb)
	{
		if (obj[i].hit_object(ray, &(obj[i]), &hit))
		{
			hit_obj = TRUE;
			if (dist_min > ray->closest_hit)
			{
				dist_min = ray->closest_hit;
				result->origin = hit.intersection;
				result->dir = hit.normal;
				copy_vec3(&result->color, *(obj[i].color));
				*hit_obj_ref = i;
			}
		}
		i++;
	}
	return (hit_obj);
}

void	prev_get_light(
	t_obj *obj, t_scene *scene, t_ray result, unsigned long *final_color, double pixel_shadow)
{
	t_vec3	light_vector;
	t_vec3	normalized_light_vector;
	double	intensity;
	t_vec3	color;
	(void)obj;

	light_vector = sub_vec3(*scene->diffuse_light->coord, result.origin);
	normalized_light_vector = get_normalized_vec3(light_vector);
	intensity = 1000 * dot_vec3(normalized_light_vector, result.dir);
	intensity /= get_norm2_vec3(light_vector);
	clamp_intensity(&intensity);
	color.coord[R] = obj->color->coord[R] * intensity * pixel_shadow;
	color.coord[G] = obj->color->coord[G] * intensity * pixel_shadow;
	color.coord[B] = obj->color->coord[B] * intensity * pixel_shadow;
	*final_color = create_trgb_struct(&color);
	// *final_color = create_trgb(255 * intensity * pixel_shadow, 255 * intensity * pixel_shadow,
	// 	255 * intensity * pixel_shadow);
}

t_vec3	*get_color_pixel(
	t_obj *obj, t_data *data, t_ray *ray, double pixel_shadow, int rebound)
{
	t_ray			result;
	t_vec3			*final_color;
	t_ray			*random_ray;
	_Bool			hit_obj;
	int				hit_obj_ref;

	hit_obj_ref = -1;
	final_color = ft_calloc(1, sizeof(t_vec3));
	final_color->coord[R] = 0;
	final_color->coord[G] = 0;
	final_color->coord[B] = 0;
	hit_obj = check_all_objects(obj, ray, &result, &hit_obj_ref);
	if (hit_obj && is_in_shadow(obj, result, data->scene->diffuse_light, hit_obj_ref))
		pixel_shadow = 0.3;
	if (!rebound)
		return ((t_vec3 *)NULL);
	if (hit_obj)
	{
		random_ray = get_random_ray(result);
		// prev_get_light(obj, scene, result, &final_color, pixel_shadow);
		*final_color = get_light(data, result, *ray, pixel_shadow);
		if (rebound > 1)
			*final_color = add_vec3(*final_color, *get_color_pixel(obj, data, random_ray, 1, --rebound));
	}
	return (final_color);
}

void	run_path_tracing(t_ray *cam_ray, t_obj *obj, unsigned long *color, t_data *data)
{
	int				i;
	t_vec3 			rgb;

	*color = 0;
	i = PASSES;
	update_camera_ray(cam_ray, data);
	// *color = get_color_pixel(obj, data->scene, cam_ray, 1, 4);
	rgb.coord[R] = 0;
	rgb.coord[G] = 0;
	rgb.coord[B] = 0;
	while (i--)
		rgb = add_vec3(rgb, *get_color_pixel(obj, data, cam_ray, 1, 4));
	rgb = div_vec3_and_const(rgb, (double)PASSES);
	*color = create_trgb_struct(&rgb);
}
