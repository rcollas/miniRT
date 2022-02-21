#include "miniRT.h"

_Bool	trace_shadow_ray(
	t_ray *shadow_ray, t_obj *obj, t_diffuse_light *light, int obj_ref)
{
	t_ray	hit;
	double	light_dist;
	double	dist_min;
	int		i;

	hit.dist = 1E99;
	i = 0;
	dist_min = 1E99;
	light_dist = get_norm_vec3(sub_vec3(*light->coord, shadow_ray->origin));
	while (i < obj->obj_nb)
	{
		if (i != obj_ref && obj->hit_object(shadow_ray, &obj[i], &hit)
			&& hit.dist < light_dist)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

_Bool	is_in_shadow(t_obj *obj, t_ray hit, t_diffuse_light *light)
{
	t_ray	shadow_ray;

	shadow_ray.origin = add_vec3(hit.origin, mul_vec3_and_const(hit.dir, 1e-4));
	shadow_ray.dir = sub_vec3(*light->coord, shadow_ray.origin);
	normalize_vec3(&shadow_ray.dir);
	if (trace_shadow_ray(&shadow_ray, obj, light, hit.obj_ref))
		return (TRUE);
	return (FALSE);
}
