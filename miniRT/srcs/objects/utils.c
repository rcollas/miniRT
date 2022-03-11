#include "miniRT.h"

void	check_direction_normal(t_ray *ray, t_obj *obj, t_ray *hit)
{
	if (dot_vec3(hit->dir, ray->dir) > 0)
	{
		hit->dir = mul_vec3_and_const(hit->dir, -1);
		obj->inside_object = TRUE;
	}
}
