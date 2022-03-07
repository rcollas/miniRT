#include "miniRT.h"

void	fill_sphere(t_parsing *var, char *line)
{
	int		i;
	t_obj	*obj;

	i = 0;
	while (var->obj_info[i])
		i++;
	if ((!BONUS && i != 4) || (BONUS && !(i == 4 || i == 5)))
	{
		error(SPHERE_FORMAT_ERROR, line);
		exit_error_parsing(SPHERE_FORMAT_ERROR, NULL, var);
	}
	obj = new_obj(SPHERE, ft_atof(var->obj_info[2]), -1, var);
	if (BONUS && i == 5)
		parse_checker(obj, var->obj_info[4]);
	fill_coordinates(var->obj_info[1], obj->origin);
	if (BONUS && var->obj_info[3] && var->obj_info[3][0] == '\"')
		parse_texture(var, obj, var->obj_info[3]);
	else
		fill_rgb(var->obj_info[3], obj->color);
	if (check(obj, SPHERE) == FAIL)
	{
		error(SPHERE_FORMAT_ERROR, line);
		exit_error_parsing(SPHERE_FORMAT_ERROR, NULL, var);
	}
	obj->hit_object = &hit_sphere;
	obj->get_uv_coord = &get_sphere_uv;
	obj->shine_factor = 0.3;
	obj_add_back(&var->objs, obj);
}

void	fill_plane(t_parsing *var, char *line)
{
	int		i;
	t_obj	*obj;

	i = 0;
	while (var->obj_info[i])
		i++;
	if ((!BONUS && i != 4) || (BONUS && !(i == 4 || i == 5)))
	{
		error(PLANE_FORMAT_ERROR, line);
		exit_error_parsing(PLANE_FORMAT_ERROR, NULL, var);
	}
	obj = new_obj(PLANE, -1, -1, var);
	if (BONUS && i == 5)
		parse_checker(obj, var->obj_info[4]);
	fill_vertex(var->obj_info[2], obj->dir);
	fill_rgb(var->obj_info[3], obj->color);
	fill_coordinates(var->obj_info[1], obj->origin);
	if (check(obj, PLANE) == FAIL)
	{
		error(PLANE_FORMAT_ERROR, line);
		exit_error_parsing(PLANE_FORMAT_ERROR, NULL, var);
	}
	obj->hit_object = &hit_plane;
	obj->get_uv_coord = &get_plane_uv;
	obj->shine_factor = 0.2;
	obj_add_back(&var->objs, obj);
}

void	fill_cylinder(t_parsing *var, char *line)
{
	int		i;
	t_obj	*obj;

	i = 0;
	while (var->obj_info[i])
		i++;
	if ((!BONUS && i != 6) || (BONUS && !(i == 6 || i == 7)))
	{
		error(CYLINDER_FORMAT_ERROR, line);
		exit_error_parsing(CYLINDER_FORMAT_ERROR, NULL, var);
	}
	obj = new_obj(CYLINDER, ft_atof(var->obj_info[3]),
			ft_atof(var->obj_info[4]), var);
	if (BONUS && i == 7)
		parse_checker(obj, var->obj_info[6]);
	fill_vertex(var->obj_info[2], obj->dir);
	fill_rgb(var->obj_info[5], obj->color);
	fill_coordinates(var->obj_info[1], obj->origin);
	if (check(obj, CYLINDER) == FAIL)
	{
		error(CYLINDER_FORMAT_ERROR, line);
		exit_error_parsing(CYLINDER_FORMAT_ERROR, NULL, var);
	}
	obj->hit_object = &hit_cylinder;
	obj->get_uv_coord = &get_cylinder_uv;
	obj->shine_factor = 0.3;
	obj_add_back(&var->objs, obj);
}

void	fill_disk(t_parsing *var, char *line)
{
	int		i;
	t_obj	*obj;

	i = 0;
	while (var->obj_info[i])
		i++;
	if ((!BONUS && i != 5) || (BONUS && !(i == 5 || i == 6)))
	{
		error(DISK_FORMAT_ERROR, line);
		exit_error_parsing(DISK_FORMAT_ERROR, NULL, var);
	}
	obj = new_obj(DISK, ft_atof(var->obj_info[3]), -1, var);
	if (BONUS && i == 6)
		parse_checker(obj, var->obj_info[5]);
	fill_coordinates(var->obj_info[1], obj->origin);
	fill_vertex(var->obj_info[2], obj->dir);
	fill_rgb(var->obj_info[4], obj->color);
	if (check(obj, DISK) == FAIL)
	{
		error(DISK_FORMAT_ERROR, line);
		exit_error_parsing(DISK_FORMAT_ERROR, NULL, var);
	}
	obj->hit_object = &hit_disk;
	obj->get_uv_coord = &get_disk_uv;
	obj->shine_factor = 0.2;
	if (BONUS && i == 6)
	{
		open_texture(obj->texture, var->obj_info[5], var);
		obj->has_texture = TRUE;
	}
	obj_add_back(&var->objs, obj);
}

void	fill_obj(int type, t_parsing *var, char *line)
{
	if (type == SPHERE)
		fill_sphere(var, line);
	if (type == PLANE)
		fill_plane(var, line);
	if (type == CYLINDER)
		fill_cylinder(var, line);
	if (type == DISK)
		fill_disk(var, line);
}
