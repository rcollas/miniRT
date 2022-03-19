#include "miniRT.h"

t_vec3	get_random_ray_dir(t_ray result, t_vec3 *vec)
{
	t_vec3	tmp1;
	t_vec3	tmp2;
	t_vec3	random_ray_dir;

	tmp1 = mul_vec3_and_const(result.dir, vec[RANDOM_DIR_LOCAL].coord[Z]);
	tmp2 = add_vec3(
			mul_vec3_and_const(vec[TANGENT_1], vec[RANDOM_DIR_LOCAL].coord[X]),
			mul_vec3_and_const(vec[TANGENT_2], vec[RANDOM_DIR_LOCAL].coord[Y]));
	random_ray_dir = add_vec3(tmp1, tmp2);
	return (random_ray_dir);
}

t_ray	*get_random_ray(t_ray result, t_data *data)
{
	t_ray	*random_ray;
	double	random_nb[2];
	t_vec3	vec[4];
	double	tmp;

	random_ray = ft_calloc(1, sizeof(t_ray));
	if (!random_ray)
		exit_error(MALLOC_ERROR, "malloc() failed", data);
	srand(ft_rand());
	random_nb[0] = frand() * 2 * M_PI;
	random_nb[1] = frand();
	tmp = sqrt(1 - random_nb[1]);
	vec[RANDOM_DIR_LOCAL].coord[X] = cos(random_nb[0]) * tmp;
	vec[RANDOM_DIR_LOCAL].coord[Y] = sin(random_nb[0]) * tmp;
	vec[RANDOM_DIR_LOCAL].coord[Z] = sqrt(random_nb[1]);
	vec[RANDOM].coord[X] = frand() - 0.5;
	vec[RANDOM].coord[Y] = frand() - 0.5;
	vec[RANDOM].coord[Z] = frand() - 0.5;
	vec[TANGENT_1] = cross_vec3(result.dir, vec[RANDOM]);
	normalize_vec3(&vec[TANGENT_1]);
	vec[TANGENT_2] = cross_vec3(vec[TANGENT_1], result.dir);
	random_ray->dir = get_random_ray_dir(result, vec);
	random_ray->origin = add_vec3(result.origin,
			mul_vec3_and_const(result.dir, 0.1));
	normalize_vec3(&random_ray->origin);
	return (random_ray);
}

_Bool	check_all_objects(t_obj *obj, t_ray *ray, t_ray *hit_min)
{
	t_ray	hit;
	_Bool	hit_obj;
	int		i;

	init_var_hit(&hit_obj, hit_min, &hit_min->color);
	i = -1;
	while (++i < obj->obj_nb)
	{
		if (obj[i].hit_object(ray, &(obj[i]), &hit))
		{
			hit_obj = TRUE;
			if (hit_min->dist > hit.dist)
			{
				hit_min->dist = hit.dist;
				copy_vec3(&hit_min->origin, hit.origin);
				copy_vec3(&hit_min->dir, hit.dir);
				copy_vec3(&hit_min->color, *obj[i].color);
				hit_min->obj_ref = i;
			}
		}
	}
	return (hit_obj);
}

t_vec3	get_color_pixel(t_obj *obj, t_data *data, t_ray *ray, int rebound)
{
	_Bool	hit_obj;
	t_ray	hit;
	t_vec3	final_color;
	t_ray	*random_ray;

	init_var_hit(&hit_obj, &hit, &final_color);
	hit_obj = check_all_objects(obj, ray, &hit);
	//if (hit_obj)
	//	compute_shadow(obj, &hit, data->scene);
	if (!rebound || (hit.shadowing == NO_SHADOW && rebound < REBOUND - 1))
		return (final_color);
	if (hit_obj)
	{
		random_ray = get_random_ray(hit, data);
		final_color = get_light(data, hit, *ray);
		final_color = add_vec3(final_color, get_color_pixel(
					obj, data, random_ray, --rebound));
	}
	final_color = mul_vec3(final_color, hit.color);
	return (final_color);
}

// t_vec3	get_color_pixel(t_obj *obj, t_data *data, t_ray *ray, int rebound)
// {
// 	t_ray	hit;
// 	t_vec3	final_color;
// 	t_ray	*random_ray;
// 	t_vec3	indirect_light;
// 	double	prob_random_ray;
// 	double	cos_theta;

// 	init_var_hit(NULL, &hit, &final_color);
// 	if (!rebound)
// 		return (final_color);
// 	if (!check_all_objects(obj, ray, &hit))
// 		return (final_color);
// 	if (is_in_shadow(obj, hit, data->scene->diffuse_light))
// 		hit.pixel_shadow = SHADOW_COEFF;
// 	if (hit.pixel_shadow == NO_SHADOW && rebound < 1)
// 		return (final_color);
// 	prob_random_ray = 1 / (2 * M_PI);
// 	random_ray = get_random_ray(hit);
// 	cos_theta = dot_vec3(random_ray->dir, hit.dir);
// 	final_color = get_light(data, hit, *ray);
// 	indirect_light = get_color_pixel(obj, data, random_ray, --rebound);
// 	indirect_light = mul_vec3_and_const(indirect_light, cos_theta * prob_random_ray);
// 	final_color = add_vec3(final_color, indirect_light);
// 	return (final_color);
// }

// t_vec3	get_color_pixel(t_obj *obj, t_data *data, t_ray *ray, int rebound)
// {
// 	t_ray	hit;
// 	t_vec3	final_color;
// 	t_ray	*random_ray;
// 	t_vec3	direct_light;
// 	t_vec3	indirect_light;
// 	double	prob_random_ray;
// 	double	cos_theta;

// 	init_var_hit(NULL, &hit, &final_color);
// 	if (!rebound)
// 		return (final_color);
// 	if (!check_all_objects(obj, ray, &hit))
// 		return (final_color);
// 	if (is_in_shadow(obj, hit, data->scene->diffuse_light))
// 		hit.pixel_shadow = SHADOW_COEFF;
// 	if (hit.pixel_shadow == NO_SHADOW && rebound < 1)
// 		return (final_color);
// 	prob_random_ray = 1 / (2 * M_PI);
// 	random_ray = get_random_ray(hit);
// 	cos_theta = dot_vec3(random_ray->dir, hit.dir);
// 	direct_light = get_light(data, hit, *ray);
// 	indirect_light = get_color_pixel(obj, data, random_ray, --rebound);
// 	indirect_light = mul_vec3_and_const(indirect_light, cos_theta * prob_random_ray);
// 	// printf("direct light = %f %f %f\n", direct_light.coord[R], direct_light.coord[G], direct_light.coord[B]);
// 	// printf("indirect light = %f %f %f\n", indirect_light.coord[R], indirect_light.coord[G], indirect_light.coord[B]);
// 	indirect_light = add_vec3(direct_light, indirect_light);
// 	final_color = mul_vec3(hit.color, indirect_light);
// 	return (final_color);
// }

void	run_path_tracing(
	t_ray *cam_ray, unsigned long *color, t_data *data, t_thread *thread)
{
	int		i;
	t_vec3	rgb;

	*color = 0;
	i = PASSES;
	data->lighting = CLASSIC_LIGHTING;
	update_camera_ray(cam_ray, data, thread);
	rgb = create_vec3(0, 0, 0);
	while (i--)
		rgb = add_vec3(rgb, get_color_pixel(data->obj, data, cam_ray, REBOUND));
	rgb = div_vec3_and_const(rgb, (double)PASSES);
	*color = create_rgb_struct(&rgb);
}
