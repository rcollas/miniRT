#include "miniRT.h"

t_vec3	get_diffuse_light(t_scene *scene, t_ray hit, t_vec3	light_dir)
{
	double	cos_theta;
	double	intensity;
	t_vec3	diffuse_light;

	normalize_vec3(&hit.dir);
	cos_theta = fmax(0.0, dot_vec3(hit.dir, light_dir));
	intensity = scene->diffuse_light->intensity * cos_theta;
	clamp_intensity(&intensity);
	diffuse_light = mul_vec3_and_const(*scene->diffuse_light->color, intensity);
	return (diffuse_light);
}

t_vec3	get_specular_light(
	t_scene *scene, t_ray hit, t_ray ray, t_vec3 light_dir)
{
	t_vec3	specular_light;
	double	intensity;
	t_vec3	reflected_ray;
	t_vec3	view_ray;
	double	cos_theta;

	specular_light = create_vec3(0, 0, 0);
	view_ray = sub_vec3(ray.origin, hit.origin);
	normalize_vec3(&view_ray);
	reflected_ray = mul_vec3_and_const(hit.dir,
			2 * dot_vec3(hit.dir, light_dir));
	reflected_ray = sub_vec3(reflected_ray, light_dir);
	cos_theta = dot_vec3(reflected_ray, view_ray);
	if (cos_theta > 0)
	{
		intensity = hit.obj->shine_factor
			* pow(fmax(0.0, cos_theta), SPECULAR_COEFF);
		clamp_intensity(&intensity);
		specular_light = mul_vec3_and_const(
			*scene->diffuse_light->color, intensity);
	}
	return (specular_light);
}

t_vec3	sum_phong_lights(
	t_data *data, t_ray hit, t_ray ray, t_vec3 light_dir)
{
	t_vec3	total_light;
	t_vec3	diffuse_light;
	t_vec3	specular_light;

	total_light = create_vec3(0, 0, 0);
	total_light = add_vec3(total_light, get_ambient_light(data->scene));
	diffuse_light = get_diffuse_light(data->scene, hit, light_dir);
	total_light = add_vec3(total_light, diffuse_light);
	specular_light = get_specular_light(data->scene, hit, ray, light_dir);
	total_light = add_vec3(total_light, specular_light);
	total_light = mul_vec3(hit.color, total_light);
	return (total_light);
}
