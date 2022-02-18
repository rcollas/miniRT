#include "miniRT.h"

t_ray	*get_random_ray(t_ray result)
{
	t_ray	*random_ray;
	double	r1;
	double	r2;
	t_vec3	vec[5];

	random_ray = ft_calloc(1, sizeof(t_ray));
	srand(ft_rand());
	r1 = frand();
	r2 = frand();
	vec[RANDOM_DIR_LOCAL].coord[X] = cos(2 * M_PI * r1) * sqrt(1 - r2);
	vec[RANDOM_DIR_LOCAL].coord[Y] = sin(2 * M_PI * r1) * sqrt(1 - r2);
	vec[RANDOM_DIR_LOCAL].coord[Z] = sqrt(r2);
	vec[RANDOM].coord[X] = frand();
	vec[RANDOM].coord[Y] = frand();
	vec[RANDOM].coord[Z] = frand();
	vec[TANGENT_1] = cross_vec3(result.dir, vec[RANDOM]);
	normalize_vec3(&vec[TANGENT_1]);
	vec[TANGENT_2] = cross_vec3(vec[TANGENT_1], result.dir);
	vec[RANDOM_DIR] = add_vec3(mul_vec3_and_const(result.dir, vec[RANDOM_DIR_LOCAL].coord[Z]),
			add_vec3(mul_vec3_and_const(vec[TANGENT_1], vec[RANDOM_DIR_LOCAL].coord[X]),
				mul_vec3_and_const(vec[TANGENT_2], vec[RANDOM_DIR_LOCAL].coord[Y])));
	random_ray->dir = vec[RANDOM_DIR];
	random_ray->origin = add_vec3(result.origin, mul_vec3_and_const(result.dir, 0.1));
	normalize_vec3(&random_ray->origin);
	return (random_ray);
}

_Bool	check_all_objects(
	t_obj *obj, t_ray *ray, t_ray *hit_min, t_obj **hit_obj_ref)
{
	t_ray	hit;
	_Bool	hit_obj;

	hit_min->dist = 1E99;
	hit_obj = FALSE;
	hit_min->color = create_vec3(0, 0, 0);
	while (obj)
	{
		if (obj->hit_object(ray, obj, &hit))
		{
			hit_obj = TRUE;
			if (hit_min->dist > hit.dist)
			{
				hit_min->dist = hit.dist;
				copy_vec3(&hit_min->origin, hit.origin);
				copy_vec3(&hit_min->dir, hit.dir);
				copy_vec3(&hit_min->color, *obj->color);
				*hit_obj_ref = obj;
			}
		}
		obj = obj->next;
	}
	return (hit_obj);
}

t_vec3	*get_color_pixel(t_obj *obj, t_data *data, t_ray *ray, int rebound)
{
	t_ray	hit;
	t_vec3	*final_color;
	t_ray	*random_ray;
	_Bool	hit_obj;
	t_obj	*hit_obj_ref;

	hit_obj_ref = NULL;
	final_color = ft_calloc(1, sizeof(t_vec3));
	final_color->coord[R] = 0;
	final_color->coord[G] = 0;
	final_color->coord[B] = 0;
	hit_obj = check_all_objects(obj, ray, &hit, &hit_obj_ref);
	if (hit_obj
		&& is_in_shadow(obj, hit, data->scene->diffuse_light, hit_obj_ref))
		hit.pixel_shadow = 0.3;
	if (!rebound)
		return ((t_vec3 *) NULL);
	if (hit_obj)
	{
		random_ray = get_random_ray(hit);
		*final_color = get_light(data, obj, hit, *ray, PHONG_LIGHTING);
		if (rebound > 1)
			*final_color = add_vec3(*final_color, *get_color_pixel(
						obj, data, random_ray, --rebound));
	}
	return (final_color);
}

void	run_path_tracing(
	t_ray *cam_ray, t_obj *obj, unsigned long *color, t_data *data)
{
	int		i;
	t_vec3	rgb;

	*color = 0;
	i = PASSES;
	update_camera_ray(cam_ray, data);
	rgb.coord[R] = 0;
	rgb.coord[G] = 0;
	rgb.coord[B] = 0;
	while (i--)
		rgb = add_vec3(rgb, *get_color_pixel(obj, data, cam_ray, 4));
	rgb = div_vec3_and_const(rgb, (double)PASSES);
	*color = create_rgb_struct(&rgb);
}
