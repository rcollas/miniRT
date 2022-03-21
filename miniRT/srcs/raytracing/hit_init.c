#include "miniRT.h"

void	init_hit(t_ray *hit)
{
	if (hit)
	{
		hit->dist = INFINITY;
		hit->shadowing = NO_SHADOW;
		hit->inside_object = FALSE;
	}
}

void	init_var_hit(_Bool *hit_obj, t_ray *hit, t_vec3 *color)
{
	if (hit_obj)
		*hit_obj = FALSE;
	init_hit(hit);
	if (color)
		*color = create_vec3(0, 0, 0);
}
