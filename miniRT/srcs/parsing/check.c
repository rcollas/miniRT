#include "miniRT.h"

int	is_in_range(double min, double max, double value)
{
	return (value >= min && value <= max);
}

int	is_valid_rgb(t_vec3 *rgb)
{
	if (!rgb)
		return (FALSE);
	if (!is_in_range((double)0, (double)255, (double)rgb->coord[R]))
		return (FALSE);
	if (!is_in_range((double)0, (double)255, (double)rgb->coord[G]))
		return (FALSE);
	if (!is_in_range((double)0, (double)255, (double)rgb->coord[B]))
		return (FALSE);
	rgb->coord[R] /= 255.0;
	rgb->coord[G] /= 255.0;
	rgb->coord[B] /= 255.0;
	return (TRUE);
}

int	is_valid_vertex(t_vec3 *vertex)
{
	if (!vertex)
		return (FALSE);
	if (!is_in_range((double) -1, (double)1, (double)vertex->coord[X]))
		return (FALSE);
	if (!is_in_range((double) -1, (double)1, (double)vertex->coord[Y]))
		return (FALSE);
	if (!is_in_range((double) -1, (double)1, (double)vertex->coord[Z]))
		return (FALSE);
	return (TRUE);
}

int	ambient_light_check(t_ambient_light *ambient_light)
{
	if (!is_in_range((double)0, (double)1, (double)ambient_light->intensity))
		return (FAIL);
	if (!is_valid_rgb(ambient_light->color))
		return (FAIL);
	return (SUCCESS);
}

int	camera_check(t_camera *camera)
{
	if (!is_valid_vertex(camera->dir))
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
	if (!is_valid_rgb(sphere->color))
		return (FAIL);
	if (BONUS && sphere->has_texture == CHECKER && !is_valid_rgb(sphere->color_checker))
		return (FAIL);
	return (SUCCESS);
}

int	plane_check(t_obj *plane)
{
	if (!is_valid_vertex(plane->dir))
		return (FAIL);
	if (!is_valid_rgb(plane->color))
		return (FAIL);
	if (BONUS && plane->has_texture == CHECKER && !is_valid_rgb(plane->color_checker))
		return (FAIL);
	return (SUCCESS);
}

int	cylinder_check(t_obj *cylinder)
{
	if (!is_valid_vertex(cylinder->dir))
		return (FAIL);
	if (cylinder->diameter <= 0)
		return (FAIL);
	if (cylinder->height <= 0)
		return (FAIL);
	if (!is_valid_rgb(cylinder->color))
		return (FAIL);
	if (BONUS && cylinder->has_texture == CHECKER && !is_valid_rgb(cylinder->color_checker))
		return (FAIL);
	return (SUCCESS);
}

int	disk_check(t_obj *disk)
{
	if (!is_valid_vertex(disk->dir))
		return (FAIL);
	if (disk->diameter <= 0)
		return (FAIL);
	if (!is_valid_rgb(disk->color))
		return (FAIL);
	if (BONUS && disk->has_texture == CHECKER && !is_valid_rgb(disk->color_checker))
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
	if (type == PLANE)
		return (plane_check((t_obj *)obj));
	if (type == CYLINDER)
		return (cylinder_check((t_obj *)obj));
	if (type == DISK)
		return (disk_check((t_obj *)obj));
	return (FAIL);
}
