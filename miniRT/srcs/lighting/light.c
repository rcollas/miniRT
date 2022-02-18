#include "miniRT.h"

t_vec3	get_ambient_light(t_scene *scene)
{
	t_vec3	ambient_light;
	double	intensity;

	intensity = scene->ambient_light->intensity;
	ambient_light = mul_vec3_and_const(*scene->ambient_light->color, intensity);
	return (ambient_light);
}

t_vec3	compute_light(t_scene *scene, t_ray hit, t_vec3 light_dir)
{
	t_vec3	normalized_light_dir;
	double	intensity;
	t_vec3	total_light;

	total_light = create_vec3(0, 0, 0);
	normalized_light_dir = get_normalized_vec3(light_dir);
	intensity = 800 * dot_vec3(normalized_light_dir, hit.dir);
	intensity /= get_norm2_vec3(light_dir);
	clamp_intensity(&intensity);
	// if ()
	total_light = mul_vec3_and_const(create_vec3(1, 1, 1), intensity);
	total_light = add_vec3(total_light, get_ambient_light(scene));
	total_light = mul_vec3(hit.color, total_light);
	return (total_light);
}

t_vec3	get_light(
	t_data *data, t_obj *obj, t_ray hit, t_ray ray, double pixel_shadow, _Bool phong_lighting)
{
	t_vec3	light_dir;
	t_vec3	total_light;

	light_dir = sub_vec3(*data->scene->diffuse_light->coord, hit.origin);
	if (!phong_lighting)
		total_light = compute_light(data->scene, hit, light_dir);
	else
	{
		normalize_vec3(&light_dir);
		total_light = sum_phong_lights(data, obj, hit, ray, light_dir);
	}
	if (dot_vec3(hit.dir, light_dir) > 0)
		total_light = mul_vec3_and_const(total_light, pixel_shadow);
	return (total_light);
}
