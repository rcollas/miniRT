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

double prev_get_light(t_scene *scene, t_ray result, double pixel_shadow)
{
	t_vec3	light_vector;
	t_vec3	normalized_light_vector;
	double	intensity;

	light_vector = sub_vec3(*scene->diffuse_light->coord, result.origin);
	normalized_light_vector = get_normalized_vec3(light_vector);
	intensity = 1000 * dot_vec3(normalized_light_vector, result.dir);
	intensity /= get_norm2_vec3(light_vector);
	intensity *= pixel_shadow;
	clamp_intensity(&intensity);
	return (intensity);
}

double	get_color_pixel(
	t_obj *obj, t_data *data, t_ray *ray, double pixel_shadow, int rebound, t_vec3 *color, double prev_intensity)
{
	t_ray			result;
	double			intensity;
	t_ray			*random_ray;
	_Bool			hit_obj;
	int				hit_obj_ref;

	hit_obj_ref = -1;
	//intensity = 0;
	hit_obj = check_all_objects(obj, ray, &result, &hit_obj_ref);
	(void)color;
	(void)prev_intensity;
	intensity = 0;
	if (hit_obj && is_in_shadow(obj, result, data->scene->diffuse_light, hit_obj_ref))
		pixel_shadow = 0.3;
	if (!rebound)
		return (0);
	if (hit_obj)
	{
		//if (rebound == 10)
		//	copy_vec3(color, result.color);
		random_ray = get_random_ray(result);
		// prev_get_light(obj, scene, result, &final_color, pixel_shadow);
		intensity = prev_get_light(data->scene, result, pixel_shadow);
		intensity = intensity - prev_intensity;
		//*final_color = sub_vec3(get_light(data, result, *ray, pixel_shadow), *previous_color);
		//*final_color = add_vec3(*final_color, *get_color_pixel(obj, data, random_ray, 1, --rebound, final_color));
		intensity += get_color_pixel(obj, data, random_ray, 1, --rebound, NULL, intensity);
	}
	return (intensity);
}

_Bool	get_rgb(t_ray ray, t_obj *obj, t_vec3 *color, t_data *data)
{
	_Bool	hit_obj;
	t_hit	hit_min;
	int 	i;
	t_ray	result;
	int		hit_obj_ref;
	t_vec3 	rgb;

	i = 0;
	hit_min.pixel_shadow = 1;
	hit_obj = FALSE;
	hit_min.dist = 1E99;
	update_camera_ray(&ray, data);
	hit_obj_ref = -1;
	rgb = create_vec3(0, 0, 0);
	while (i < data->obj_nb)
	{
		if (check_hit_object(&ray, &obj[i], &hit_min))
		{
			hit_obj_ref = i;
			hit_obj = TRUE;
		}
		i++;
	}
	if (hit_obj)
	{
		result.origin = hit_min.intersection;
		result.dir = hit_min.normal;
		result.color = hit_min.color;
		if (is_in_shadow(obj, result, data->scene->diffuse_light, hit_obj_ref))
			hit_min.pixel_shadow = 0.3;
		rgb = get_light(data, result, ray, hit_min.pixel_shadow);
	}
	*color = rgb;
	return (hit_obj);
}

void	run_path_tracing(t_ray *cam_ray, t_obj *obj, unsigned long *color, t_data *data)
{
	int				i;
	double			intensity;
	t_vec3			rgb;

	*color = 0;
	rgb = create_vec3(0, 0, 0);
	i = PASSES;
	update_camera_ray(cam_ray, data);
	intensity = 0;
	// *color = get_color_pixel(obj, data->scene, cam_ray, 1, 4);
	get_rgb(*cam_ray, data->obj, &rgb, data);
	while (i--)
		intensity += get_color_pixel(obj, data, cam_ray, 1, 4, &rgb, 0);
	intensity /= PASSES;
	//printf("rgb R = %f\n", rgb.coord[R]);
	//printf("rgb G = %f\n", rgb.coord[G]);
	//printf("rgb B = %f\n", rgb.coord[B]);
	if (intensity)
	{
		rgb.coord[R] *=  1 + intensity;
		rgb.coord[G] *= 1 + intensity;
		rgb.coord[B] *= 1 + intensity;
	}
	*color = create_trgb_struct(&rgb);
}
