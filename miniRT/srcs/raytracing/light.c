#include "miniRT.h"

t_vec3	get_ambient_light(t_scene *scene, t_ray hit)
{
	t_vec3	ambient_light;
	double	intensity;

	(void)hit;
	intensity = scene->ambient_light->intensity;
	ambient_light = mul_vec3_and_const(*scene->ambient_light->color, intensity);
	return (ambient_light);
}

t_vec3	get_diffuse_light(t_scene *scene, t_ray hit, t_vec3	light_dir)
{
	double	cos_theta;
	double	intensity;
	t_vec3	diffuse_light;
	
	normalize_vec3(&hit.dir);
	cos_theta = fmax(0.0, dot_vec3(hit.dir, light_dir));
	intensity = scene->diffuse_light->intensity * cos_theta;
	clamp_intensity(&intensity);
	diffuse_light = mul_vec3_and_const(create_vec3(1, 1, 1), intensity);
	return (diffuse_light);
}

t_vec3	get_reflected_ray(t_vec3 normal, t_vec3 light_dir)
{
	t_vec3	reflected_ray;

	reflected_ray = mul_vec3_and_const(normal, 2 * dot_vec3(normal, light_dir));
	reflected_ray = sub_vec3(reflected_ray, light_dir);
	return (reflected_ray);
}

t_vec3	get_specular_light(t_scene *scene, t_ray hit, t_ray ray, t_vec3	light_dir)
{
	t_vec3	specular_light;
	double	intensity;
	t_vec3	reflected_ray;
	t_vec3	view_ray;
	double	cos_theta;

	(void)scene;
	specular_light = create_vec3(0, 0, 0);
	view_ray = sub_vec3(ray.origin, hit.origin);
	normalize_vec3(&view_ray);
	reflected_ray = get_reflected_ray(hit.dir, light_dir);
	cos_theta = dot_vec3(reflected_ray, view_ray);
	if (cos_theta > 0)
	{
	// cos_theta /= (get_norm_vec3(reflected_ray) * get_norm_vec3(view_ray));
		intensity = 0.3 * pow(fmax(0.0, cos_theta), 16);
		clamp_intensity(&intensity);
		specular_light = mul_vec3_and_const(create_vec3(1, 1, 1), intensity);
	}
	return (specular_light);
}

t_vec3	sum_total_light(t_scene *scene, t_ray hit, t_ray ray, t_vec3 light_dir)
{
	t_vec3	total_light;

	(void)ray;
	(void)light_dir;
	total_light = create_vec3(0, 0, 0);
	total_light = add_vec3(total_light, get_ambient_light(scene, hit));
	total_light = add_vec3(total_light, get_diffuse_light(scene, hit, light_dir));
	total_light = add_vec3(total_light, get_specular_light(scene, hit, ray, light_dir));
	total_light = mul_vec3(hit.color, total_light);
	return (total_light);
}

t_vec3	*get_light(t_scene *scene, t_ray hit, t_ray ray, unsigned long *color, double pixel_shadow)
{
	t_vec3	light_dir;
	t_vec3	*total_light;

	(void)color;
	total_light = ft_calloc(1, sizeof(t_vec3));
	light_dir = sub_vec3(*scene->diffuse_light->coord, hit.origin);
	normalize_vec3(&light_dir);
	*total_light = sum_total_light(scene, hit, ray, light_dir);
	*total_light = mul_vec3_and_const(*total_light, pixel_shadow);
	return (total_light);
	//*color = create_trgb_struct(98, &total_light);
}
