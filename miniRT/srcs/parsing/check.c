#include "../../incs/miniRT.h"

int	is_in_range(double min, double max, double value)
{
	return (value >= min && value <= max);
}

int	is_valid_rgb(t_rgb *rgb)
{
	if (!rgb) {
		return (FALSE);
	}
	if (!is_in_range((double)0, (double)255, (double)rgb->r))
		return (FALSE);
	if (!is_in_range((double)0, (double)255, (double)rgb->g))
		return (FALSE);
	if (!is_in_range((double)0, (double)255, (double)rgb->b))
		return (FALSE);
	return (TRUE);
}

int	is_valid_vertex(t_vertex *vertex)
{
	if (!vertex)
		return (FALSE);
	if (!is_in_range((double)-1, (double)1, (double)vertex->x))
		return (FALSE);
	if (!is_in_range((double)-1, (double)1, (double)vertex->y))
		return (FALSE);
	if (!is_in_range((double)-1, (double)1, (double)vertex->z))
		return (FALSE);
	return (TRUE);
}

int	ambient_light_check(t_ambient_light *ambient_light)
{
	if (!is_in_range((double)0, (double)1, (double)ambient_light->intensity))
		return (FAIL);

	if (!is_valid_rgb(ambient_light->rgb))
		return (FAIL);
	return (SUCCESS);
}

int	camera_check(t_camera *camera)
{
	if (!is_valid_vertex(camera->vertex))
		return (FAIL);
	if (!is_in_range((double)0, (double)180, (float)camera->fov))
		return (FAIL);
	return (SUCCESS);
}

int	diffuse_light_check(t_diffuse_light *diffuse_light)
{
	if (!is_in_range((double)0, (double)1, diffuse_light->intensity))
		return (FAIL);
	return (SUCCESS);
}

int	sphere_check(t_obj *sphere)
{
	if (sphere->diameter <= 0)
		return (FAIL);
	if (!is_valid_rgb(sphere->rgb))
		return (FAIL);
	return (SUCCESS);
}

int	plan_check(t_obj *plan)
{
	if (!is_valid_vertex(plan->vertex))
		return (FAIL);
	if (!is_valid_rgb(plan->rgb))
		return (FAIL);
	return (SUCCESS);
}

int	cylinder_check(t_obj *cylinder)
{
	if (!is_valid_vertex(cylinder->vertex))
		return (FAIL);
	if (cylinder->diameter <= 0)
		return (FAIL);
	if (cylinder->height <= 0)
		return (FAIL);
	if (!is_valid_rgb(cylinder->rgb))
		return (FAIL);
	return (SUCCESS);
}

int	check(void *obj, int type)
{
	if (type == AMBIENT_LIGHT)
		return (ambient_light_check((t_ambient_light *)obj));
	if (type == CAMERA)
		return (camera_check((t_camera *)obj));
	if (type == DIFFUSE_LIGHT)
		return (diffuse_light_check((t_diffuse_light *)obj));
	if (type == SPHERE)
		return (sphere_check((t_obj *)obj));
	if (type == PLAN)
		return (plan_check((t_obj *)obj));
	if (type == CYLINDER)
		return (cylinder_check((t_obj *)obj));
	return (FAIL);
}