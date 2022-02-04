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

// void	get_color_pixel(t_scene *scene, t_hit hit, int *color, double pixel_shadow)
// {
// 	double	diffuse_shading;
// 	t_rgb	color_pixel;
// 	t_rgb	ambient_light;

// 	(void)pixel_shadow;
// 	color_pixel = init_color(0, 0 ,0);
// 	diffuse_shading = get_diffuse_shading(scene, hit);
// 	color_pixel = mul_rgb_and_const(hit.color, diffuse_shading);
// 	ambient_light = get_ambient_light(scene, hit);
// 	color_pixel = add_rgb(color_pixel, ambient_light);
// 	color_pixel = mul_rgb(color_pixel, *scene->ambient_light->color);
// 	*color = create_trgb_struct(98, &color_pixel);
// }

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

// double	get_light_brightness(t_scene *scene, t_hit hit)
// {
// 	t_vec3	light_dir;
// 	double	distance;
// 	double	brightness;

// 	light_dir = sub_vec3(*scene->diffuse_light->coord, hit.intersection);
// 	distance = sqrtf(get_norm_vec3(light_dir));
// 	brightness = 1.0 /(1.0 + distance * 0.5);
// 	return (brightness);
// }


// t_rgb	get_specular_light(t_scene *scene, t_hit hit, t_ray ray)
// {
// 	t_rgb	specular_light;
// 	t_vec3	light_dir;
// 	double	intensity;
// 	t_vec3	reflected_ray;
// 	t_vec3	h;
// 	double	cos_theta;

// 	light_dir = sub_vec3(*scene->diffuse_light->coord, hit.intersection);
// 	normalize_vec3(&light_dir);
// 	h = sub_vec3(ray.origin, hit.intersection);
// 	reflected_ray = sub_vec3(mul_vec3_and_const(hit.normal, 2 * dot_vec3(hit.normal, light_dir)), light_dir);
// 	cos_theta = fmax(0, vcos(reflected_ray, h));
// 	intensity = scene->diffuse_light->intensity * pow(cos_theta, 100);
// 	clamp_intensity(&intensity);
// 	specular_light = mul_rgb_and_const(hit.color, intensity);
// 	return (specular_light);
// }
