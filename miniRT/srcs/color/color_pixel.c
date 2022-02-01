#include "miniRT.h"

// void	get_color_pixel(t_scene *scene, t_hit hit, int *color, double pixel_shadow)
// {
// 	t_vec3		light_dir;
// 	t_vec3		light_dir_norm;
// 	double		intensity;
// 	t_rgb		final_color;

// 	light_dir = sub_vec3(*scene->diffuse_light->coord, hit.intersection);
// 	light_dir_norm = get_normalized_vec3(light_dir);
// 	intensity = 1000 * dot_vec3(light_dir_norm, hit.normal) * scene->diffuse_light->intensity;
// 	intensity /= get_norm2_vec3(light_dir);
// 	// printf("intensity = %f\n", intensity);
// 	clamp_intensity(&intensity);
// 	final_color = mul_rgb_and_const(hit.color, intensity * pixel_shadow);
// 	// final_color.r = hit.color.r * intensity * pixel_shadow; // + scene->ambient_light->color->r * scene->ambient_light->intensity;
// 	// final_color.g = hit.color.g * intensity * pixel_shadow; // + scene->ambient_light->color->g * scene->ambient_light->intensity;
// 	// final_color.b = hit.color.b * intensity * pixel_shadow; // + scene->ambient_light->color->b * scene->ambient_light->intensity;
// 	*color = create_trgb_struct(98, &final_color);
// }

double	get_diffuse_shading(t_scene *scene, t_hit hit)
{
	t_vec3	light_dir;
	double	cos_theta;
	double	diffuse_shading;

	light_dir = sub_vec3(*scene->diffuse_light->coord, hit.intersection);
	normalize_vec3(&light_dir);
	cos_theta = dot_vec3(light_dir, hit.normal);
	clamp_intensity(&cos_theta);
	diffuse_shading = scene->diffuse_light->intensity / M_PI * cos_theta;
	return (diffuse_shading);
}

t_rgb	get_ambient_light(t_scene *scene, t_hit hit)
{
	t_rgb	ambient_light;
	double	intensity;

	intensity = scene->ambient_light->intensity / M_PI;
	ambient_light = mul_rgb_and_const(hit.color, intensity);
	return (ambient_light);
}

void	get_color_pixel(t_scene *scene, t_hit hit, int *color, double pixel_shadow)
{
	double	diffuse_shading;
	t_rgb	color_pixel;
	t_rgb	ambient_light;

	(void)pixel_shadow;
	color_pixel = init_color(0, 0 ,0);
	diffuse_shading = get_diffuse_shading(scene, hit);
	color_pixel = mul_rgb_and_const(hit.color, diffuse_shading);
	ambient_light = get_ambient_light(scene, hit);
	color_pixel = add_rgb(color_pixel, ambient_light);
	color_pixel = mul_rgb(color_pixel, *scene->ambient_light->color);
	*color = create_trgb_struct(98, &color_pixel);
}

	// ambient_color = mul_rgb_and_const(hit.color, intensity);
	// final_color = add_rgb(final_color, ambient_color);
	// final_color = mul_rgb(final_color, *scene->ambient_light->color);
// colored = 
// add_colors( 			// color1.r + color2.r
// 	- color_pixel, 
// 	- mix_colors(		// color1.r * color2.r
// 		- shade_color(	// color1.r * coeff
// 			- current_light.obj_prop.light.intensity / M_PI * fmax(0, fmin(1, dot_product)),
// 			- closest_obj.color),
// 		- current_light.color));