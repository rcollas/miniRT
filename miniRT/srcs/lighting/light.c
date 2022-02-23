#include "miniRT.h"

t_vec3	get_ambient_light(t_scene *scene)
{
	t_vec3	ambient_light;
	double	intensity;

	intensity = scene->ambient_light->intensity;
	ambient_light = mul_vec3_and_const(*scene->ambient_light->color, intensity);
	return (ambient_light);
}

// t_vec3	compute_classic_light(t_scene *scene, t_ray hit, t_vec3 light_dir)
// {
// 	t_vec3	normalized_light_dir;
// 	double	intensity;
// 	t_vec3	total_light;

// 	total_light = create_vec3(0, 0, 0);
// 	normalized_light_dir = get_normalized_vec3(light_dir);
// 	intensity = 800 * dot_vec3(normalized_light_dir, hit.dir);
// 	intensity /= get_norm2_vec3(light_dir);
// 	clamp_intensity(&intensity);
	// if (hit.pixel_shadow == 1)
		// total_light = mul_vec3_and_const(*scene->diffuse_light->color, intensity);
// 	total_light = add_vec3(total_light, get_ambient_light(scene));
// 	total_light = mul_vec3(hit.color, total_light);
// 	return (total_light);
// }

t_vec3	compute_classic_light(t_scene *scene, t_ray hit, t_vec3 light_dir)
{
	t_vec3	normalized_light_dir;
	double	intensity;
	t_vec3	total_light;

	total_light = create_vec3(0, 0, 0);
	normalized_light_dir = get_normalized_vec3(light_dir);
	intensity = 3 * dot_vec3(normalized_light_dir, hit.dir);
	intensity *= (scene->diffuse_light->intensity / M_PI);
	clamp_intensity(&intensity);
	// if (hit.pixel_shadow == 1)
	if (dot_vec3(hit.dir, light_dir) > 0)
		intensity *= hit.pixel_shadow;
	total_light = mul_vec3_and_const(*scene->diffuse_light->color, intensity);
	total_light = add_vec3(total_light, get_ambient_light(scene));
	total_light = mul_vec3(hit.color, total_light);
	return (total_light);
}

t_vec3	get_light(t_data *data, t_ray hit, t_ray ray)
{
	t_vec3	light_dir;
	t_vec3	total_light;

	light_dir = sub_vec3(*data->scene->diffuse_light->coord, hit.origin);
	if (data->lighting == PHONG_LIGHTING)
	{
		normalize_vec3(&light_dir);
		total_light = sum_phong_lights(data, hit, ray, light_dir);
	}
	else
		total_light = compute_classic_light(data->scene, hit, light_dir);
	// if (dot_vec3(hit.dir, light_dir) > 0)
	// 	total_light = mul_vec3_and_const(total_light, hit.pixel_shadow);
	return (total_light);
}
