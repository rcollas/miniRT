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

	total_light = create_vec3(0, 0, 0);
	hit.shadowing = compute_shadow(
			data->obj, &hit, scene->diffuse_light);
	light_dir = sub_vec3(*scene->diffuse_light->coord, hit.origin);
	normalize_vec3(&light_dir);
	intensity = 3 * dot_vec3(light_dir, hit.dir);
	intensity *= (scene->diffuse_light->intensity / M_PI);
	intensity *= hit.shadowing;
	clamp_intensity(&intensity);
	total_light = add_vec3(total_light, mul_vec3_and_const(
				create_vec3(1, 1, 1), intensity));
	return (total_light);
}

t_vec3	get_light(t_data *data, t_ray hit)
{
	t_vec3	total_light;

	total_light = create_vec3(0, 0, 0);
	if (!hit.inside_object)
		total_light = compute_classic_light(data->scene, hit, data);
	total_light = add_vec3(total_light, get_ambient_light(data->scene));
	return (total_light);
}
