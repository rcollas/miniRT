#include "miniRT.h"

_Bool	hit_disk(t_ray *ray, t_obj *obj, t_ray *hit)
{
	double	radius2;
	t_vec3	v;
	double	dist;

	if (!hit_plane(ray, obj, hit))
		return (FALSE);
	radius2 = (obj->diameter * 0.5) * (obj->diameter * 0.5);
	v = sub_vec3(*obj->origin, hit->origin);
	dist = dot_vec3(v, v);
	if (dist <= radius2)
		return (TRUE);
	return (FALSE);
}
