#include "miniRT.h"

void	get_color_pixel(t_scene *scene, t_hit hit, int *color, double pixel_shadow)
{
	t_vec3		light_vector;
	t_vec3		normalized_light_vector;
	double		intensity;

	light_vector = sub_vec3(*scene->diffuse_light->coord, hit.intersection);
	normalized_light_vector = get_normalized_vec3(light_vector);
	intensity = 1000 * dot_vec3(normalized_light_vector, hit.normal);
	intensity /= get_norm2_vec3(light_vector);
	intensity *= pixel_shadow;
	// printf("intensity = %f\n", intensity);
	clamp_intensity(&intensity);
	*color = create_trgb(98, hit.color.r * intensity, hit.color.g * intensity, hit.color.b * intensity);
}
