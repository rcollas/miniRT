#include "miniRT.h"

unsigned short lfsr = 0xACE1u;
unsigned bit;

unsigned ft_rand()
{

	bit  = ((lfsr >> 0) ^ (lfsr >> 2) ^ (lfsr >> 3) ^ (lfsr >> 5) ) & 1;
	return lfsr =  (lfsr >> 1) | (bit << 15);
}

float	frand()
{
	float	rand;

	rand = (float)ft_rand();
	while (rand > 1)
		rand /= 10;
	printf("%f\n", rand);
	return (rand);
}

void	get_color_pixel(t_scene *scene, t_ray hit, int *color, double pixel_shadow)
{
	t_vec3		light_vector;
	t_vec3		normalized_light_vector;
	double		intensity;

	light_vector = sub_vec3(*scene->diffuse_light->coord, hit.origin);
	normalized_light_vector = get_normalized_vec3(light_vector);
	intensity = 1000 * dot_vec3(normalized_light_vector, hit.dir);
	intensity /= get_norm2_vec3(light_vector);
	intensity *= scene->diffuse_light->intensity;
	intensity *= pixel_shadow;
	clamp_intensity(&intensity);
	*color = create_trgb(98, hit.color.r * intensity,
			hit.color.g * intensity, hit.color.b * intensity);
}
