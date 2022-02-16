#include "miniRT.h"

_Bool	check_hit_object(t_ray *ray, t_obj *obj, t_hit *hit_min, t_obj **hit_obj_ref)
{
	t_hit	hit;

	if (obj->hit_object(ray, obj, &hit))
	{
		if (hit_min->dist > ray->closest_hit)
		{
			hit_min->dist = ray->closest_hit;
			copy_vec3(&hit_min->intersection, hit.intersection);
			copy_vec3(&hit_min->normal, hit.normal);
			copy_vec3(&hit_min->color, *obj->color);
			*hit_obj_ref = obj;
		}
		return (TRUE);
	}
	return (FALSE);
}

_Bool	prev_detect_intersection(t_ray ray, t_obj *obj, unsigned long *color, t_data *data)
{
	_Bool	hit_obj;
	t_hit	hit_min;
	t_obj	*current_obj;
	t_obj 	*no_check;
	t_ray	result;
	t_obj	*hit_obj_ref;

	hit_min.pixel_shadow = 1;
	hit_obj = FALSE;
	hit_min.dist = 1E99;
	update_camera_ray(&ray, data);
	current_obj = obj;
	hit_obj_ref = NULL;
	while (current_obj)
	{
		if (check_hit_object(&ray, current_obj, &hit_min, &hit_obj_ref))
		{
			no_check = current_obj;
			hit_obj = TRUE;
		}
		current_obj = current_obj->next;
	}
	if (hit_obj)
	{
		result.origin = hit_min.intersection;
		result.dir = hit_min.normal;
		result.color = hit_min.color;
		if (is_in_shadow(obj, result, data->scene->diffuse_light, hit_obj_ref))
			hit_min.pixel_shadow = 0.3;
		get_light(data->scene, result, ray, color, hit_min.pixel_shadow);
	}
	return (hit_obj);
}
