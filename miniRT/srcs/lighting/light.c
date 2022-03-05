#include "miniRT.h"

t_vec3	get_ambient_light(t_scene *scene)
{
	t_vec3	ambient_light;
	double	intensity;

	intensity = scene->ambient_light->intensity;
	ambient_light = mul_vec3_and_const(*scene->ambient_light->color, intensity);
	return (ambient_light);
}

t_vec3	compute_classic_light(t_scene *scene, t_ray hit, t_data *data)
{
	t_vec3	light_dir;
	double	intensity;
	t_vec3	total_light;
	int		i;
	double	shadowing;

	total_light = create_vec3(0, 0, 0);
	i = -1;
	while (++i < scene->light_nb)
	{
		shadowing = compute_shadow(data->obj, &hit, &scene->diffuse_light[i]);
		light_dir = sub_vec3(*scene->diffuse_light[i].coord, hit.origin);
		normalize_vec3(&light_dir);
		intensity = 3 * dot_vec3(light_dir, hit.dir);
		intensity *= (scene->diffuse_light[i].intensity / M_PI);
		intensity *= shadowing;
		clamp_intensity(&intensity);
		total_light = add_vec3(total_light, mul_vec3_and_const(
				*scene->diffuse_light[i].color, intensity));
	}
	total_light = add_vec3(total_light, get_ambient_light(scene));
	return (total_light);
}

t_vec3	get_light(t_data *data, t_ray hit, t_ray ray)
{
	t_vec3	total_light;
	t_vec3	light_dir;

	light_dir = sub_vec3(*data->scene->diffuse_light->coord, hit.origin);
	if (data->lighting == PHONG_LIGHTING)
	{
		normalize_vec3(&light_dir);
		total_light = sum_phong_lights(data, hit, ray, light_dir);
	}
	else
		total_light = compute_classic_light(data->scene, hit, data);
	return (total_light);
}
