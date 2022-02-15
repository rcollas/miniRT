#include "miniRT.h"

unsigned int	ft_rand()
{
	int	fd;
	unsigned buff;
	unsigned *bit;

	fd = open("/dev/urandom", O_RDONLY);
	read(fd, &buff, sizeof(unsigned));
	bit = &buff;
	close(fd);
	return (*bit);
}

float	frand()
{
	float	float_rand;

	float_rand = (float)ft_rand();
	//while (float_rand == 0)
	//	float_rand = (float)ft_rand();
	while (float_rand > 1)
		float_rand /= 10;
	return (float_rand);
}

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
	random_ray->origin = add_vec3(result.origin, mul_vec3_and_const(result.dir, 0.001));
	random_ray->dir = random_dir;
	return (random_ray);
}

_Bool	check_all_objects(t_obj *obj, t_ray *ray, t_ray *result)
{
	t_hit	hit;
	_Bool	hit_obj;
	double	dist_min;

	dist_min = 1E99;
	hit_obj = FALSE;
	result->color = create_vec3(0, 0, 0);
	while (obj)
	{
		if (obj->hit_object(ray, obj, &hit))
		{
			hit_obj = TRUE;
			if (dist_min > ray->closest_hit)
			{
				dist_min = ray->closest_hit;
				result->origin = hit.intersection;
				result->dir = hit.normal;
				result->color = *obj->color;
			}
		}
		obj = obj->next;
	}
	return (hit_obj);
}

void	prev_get_light(t_obj *obj, t_scene *scene, t_ray result, unsigned long *final_color, double pixel_shadow)
{
	t_vec3	light_vector;
	t_vec3	normalized_light_vector;
	double	intensity;
	t_vec3	color;

	light_vector = sub_vec3(*scene->diffuse_light->coord, result.origin);
	normalized_light_vector = get_normalized_vec3(light_vector);
	intensity = 1000 * dot_vec3(normalized_light_vector, result.dir);
	intensity /= get_norm2_vec3(light_vector);
	clamp_intensity(&intensity);
	color.coord[R] = obj->color->coord[R] * intensity * pixel_shadow;
	color.coord[G] = obj->color->coord[G] * intensity * pixel_shadow;
	color.coord[B] = obj->color->coord[B] * intensity * pixel_shadow;
	*final_color = create_trgb_struct(98, &color);
}

unsigned long	get_color_pixel(
	t_obj *obj, t_scene *scene, t_ray *ray, double pixel_shadow, int rebound)
{
	t_ray			result;
	unsigned long	final_color;
	t_ray			*random_ray;
	_Bool			hit_obj;

	pixel_shadow = 1;
	final_color = 0;
	hit_obj = check_all_objects(obj, ray, &result);
	if (hit_obj && is_in_shadow(obj, result, scene->diffuse_light))
		pixel_shadow = 0.3;
	if (!rebound)
		return (0);
	if (hit_obj)
	{
		random_ray = get_random_ray(result);
		// prev_get_light(obj, scene, result, &final_color, pixel_shadow);
		get_light(scene, result, *ray, &final_color, pixel_shadow);
		final_color += get_color_pixel(obj, scene, random_ray, 1, --rebound);
	}
	else
		final_color = create_trgb(98, 0, 0, 0);
	return (final_color);
}


// unsigned long	get_color_pixel(t_obj *obj, t_scene *scene, t_ray *ray, double pixel_shadow, int rebound)
// {

// 	_Bool	hit_obj;
// 	double	dist_min;
// 	t_obj	*current_obj;
// 	t_ray	result;
// 	t_hit	hit;

// 	current_obj = obj;
// 	pixel_shadow = 1;
// 	hit_obj = FALSE;
// 	dist_min = 1E99;
// 	while (current_obj)
// 	{
// 		if (obj->hit_object(ray, current_obj, &hit))
// 		{
// 			hit_obj = TRUE;
// 			if (dist_min > ray->closest_hit)
// 			{
// 				dist_min = ray->closest_hit;
// 				result.origin = hit.intersection;
// 				result.dir = hit.normal;
// 			}
// 		}
// 		current_obj = current_obj->next;
// 	}

// 	if (is_in_shadow(obj, result, scene->diffuse_light) == TRUE)
// 		pixel_shadow = 0.3;
// 	t_vec3		light_vector;
// 	t_vec3		normalized_light_vector;
// 	double		intensity;
// 	int			final_color;
// 	//indirect lighting
// 	double		r1;
// 	double 		r2;
// 	t_vec3		random_dir_local;
// 	t_vec3		random_dir;
// 	t_vec3		random;
// 	t_vec3		tangent1;
// 	t_vec3		tangent2;
// 	t_ray		*random_ray;
// 	random_ray = malloc(sizeof(t_ray));
// 	if (rebound == 0)
// 		return (0);
// 	if (hit_obj == TRUE) {
// 		r1 = frand();
// 		r2 = frand();
// 		random_dir_local.coord[X] = cos(2 * M_PI * r1) * sqrt(1 - r2);
// 		random_dir_local.coord[Y] = sin(2 * M_PI * r1) * sqrt(1 - r2);
// 		random_dir_local.coord[Z] = sqrt(r2);

// 		random.coord[X] = frand();
// 		random.coord[Y] = frand();
// 		random.coord[Z] = frand();

// 		tangent1 = cross_vec3(result.dir, random);
// 		normalize_vec3(&tangent1);
// 		tangent2 = cross_vec3(tangent1, result.dir);

// 		//random_dir = mul_vec3_and_const(normal, random_dir_local.z);
// 		//random_dir = add_vec3(random_dir, mul_vec3_and_const(tangent1, random_dir_local.x));
// 		//random_dir = add_vec3(random_dir, mul_vec3_and_const(tangent2, random_dir_local.y));

// 		random_dir = add_vec3(mul_vec3_and_const(result.dir, random_dir_local.coord[Z]),
// 							  add_vec3(mul_vec3_and_const(tangent1, random_dir_local.coord[X]),
// 									   mul_vec3_and_const(tangent2, random_dir_local.coord[Y])));

// 		//random_ray.origin = add_vec3(intersection, mul_vec3_and_const(normal, 0.001));
// 		random_ray->origin = add_vec3(result.origin, mul_vec3_and_const(result.dir, 0.001));
// 		random_ray->dir = random_dir;
// 		//printf("random_ray.dir x = %f\n", random_ray.dir.x);

// 		light_vector = sub_vec3(*scene->diffuse_light->coord, result.origin);
// 		normalized_light_vector = get_normalized_vec3(light_vector);
// 		intensity = 1000 * dot_vec3(normalized_light_vector, result.dir);
// 		intensity /= get_norm2_vec3(light_vector);
// 		//intensity += get_color_pixel(obj, scene, random_ray, color, 1, --rebound);
// 		final_color = create_trgb(98, 255 * intensity * pixel_shadow, 255 * intensity * pixel_shadow,
// 								  255 * intensity * pixel_shadow);
// 		final_color += get_color_pixel(obj, scene, random_ray, 1, --rebound);
// 		clamp_intensity(&intensity);
// 		//printf("intensity = %f\n", intensity);
// 	}
// 	else
// 		final_color = create_trgb(98, 0, 0, 0);
// 	//printf("intensity = %f\n", intensity); *color = final_color;
// 	return (final_color);
// }
