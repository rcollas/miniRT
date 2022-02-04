#include "miniRT.h"

t_vec3	get_ambient_light(t_scene *scene, t_hit hit)
{
	t_vec3	ambient_light;
	double	intensity;

	intensity = scene->ambient_light->intensity;
	ambient_light = mul_vec3_and_const(hit.color, intensity);
	ambient_light = mul_vec3(ambient_light, *scene->ambient_light->color);
	return (ambient_light);
}

t_vec3	get_diffuse_light(t_scene *scene, t_hit hit, t_vec3	light_dir)
{
	double	cos_theta;
	double	intensity;
	t_vec3	diffuse_light;

	cos_theta = fmax(0, dot_vec3(light_dir, hit.normal));
	intensity = scene->diffuse_light->intensity * cos_theta;
	clamp_intensity(&intensity);
	diffuse_light = mul_vec3_and_const(hit.color, intensity);
	return (diffuse_light);
}

t_vec3	get_reflected_ray(t_vec3 normal, t_vec3 light_dir)
{
	t_vec3	reflected_ray;

	reflected_ray = mul_vec3_and_const(normal, 2 * dot_vec3(normal, light_dir));
	reflected_ray = sub_vec3(reflected_ray, light_dir);
	return (reflected_ray);
}

t_vec3	get_specular_light(t_scene *scene, t_hit hit, t_ray ray, t_vec3	light_dir)
{
	t_vec3	specular_light;
	double	intensity;
	t_vec3	reflected_ray;
	t_vec3	view_ray;
	double	cos_theta;

	view_ray = sub_vec3(ray.origin, hit.intersection);
	reflected_ray = get_reflected_ray(hit.normal, light_dir);
	cos_theta = dot_vec3(reflected_ray, view_ray);
	cos_theta /= (get_norm_vec3(reflected_ray) * get_norm_vec3(view_ray));
	intensity = scene->diffuse_light->intensity * pow(cos_theta, 100);
	clamp_intensity(&intensity);
	specular_light = mul_vec3_and_const(hit.color, intensity);
	return (specular_light);
}

t_vec3	sum_total_light(t_scene *scene, t_hit hit, t_ray ray, t_vec3 light_dir)
{
	t_vec3	total_light;

	total_light = create_vec3(0, 0, 0);
	total_light = add_vec3(total_light, get_ambient_light(scene, hit));
	total_light = add_vec3(total_light, get_diffuse_light(scene, hit, light_dir));
	total_light = add_vec3(total_light, get_specular_light(scene, hit, ray, light_dir));
	return (total_light);
}

void	get_color_pixel(t_scene *scene, t_hit hit, t_ray ray, int *color)
{
	t_vec3	light_dir;
	t_vec3	total_light;
	
	// printf("shadow = %f\n", hit.pixel_shadow);
	light_dir = sub_vec3(*scene->diffuse_light->coord, hit.intersection);
	normalize_vec3(&light_dir);
	total_light = sum_total_light(scene, hit, ray, light_dir);
	total_light = mul_vec3_and_const(total_light, hit.pixel_shadow);
	*color = create_trgb_struct(98, &total_light);
}
