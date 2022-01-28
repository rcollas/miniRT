#include "miniRT.h"

void	get_color_pixel(t_scene *scene, t_vec3 intersection, t_vec3 normal, int *color, double pixel_shadow)
{
	t_vec3		light_vector;
	t_vec3		normalized_light_vector;
	double		intensity;

	light_vector = sub_vec3(*scene->diffuse_light->coord, intersection);
	normalized_light_vector = get_normalized_vec3(light_vector);
	intensity = 1000 * dot_product_vec3(normalized_light_vector, normal);
	intensity /= get_norm2_vec3(light_vector);
	// printf("intensity = %f\n", intensity);
	clamp_intensity(&intensity);
	*color = create_trgb(98, 136 * intensity * pixel_shadow, 32 * intensity * pixel_shadow, 250 * intensity * pixel_shadow);
}
