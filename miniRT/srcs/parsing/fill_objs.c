#include "miniRT.h"

void	fill_sphere(t_parsing *var, char *line)
{
	int		i;
	int		ret;
	t_obj	*obj;

	i = 0;
	while (var->obj_info[i])
		i++;
	if ((!BONUS && i != 4) || (BONUS && !(i == 4 || i == 5)))
		exit_error_parsing(error(SPHERE_FORMAT_ERROR, line), NULL, var);
	obj = new_obj(SPHERE, ft_atof(var->obj_info[2]), -1, var);
	ret = fill_coordinates(var->obj_info[1], obj->origin);
	if (BONUS && i == 5)
		ret += parse_checker(obj, var->obj_info[4]);
	if (BONUS && var->obj_info[3] && var->obj_info[3][0] == '\"')
		parse_texture(var, obj, var->obj_info[3]);
	else
		ret += fill_rgb(var->obj_info[3], obj->color);
	if (check(obj, SPHERE) == FAIL || ret)
		exit_error_parsing(error(SPHERE_FORMAT_ERROR, line), NULL, var);
	obj->hit_object = &hit_sphere;
	obj->get_uv_coord = &get_sphere_uv;
	obj->shine_factor = 0.3;
	obj_add_back(&var->objs, obj);
}

void	fill_plane(t_parsing *var, char *line)
{
	int		i;
	int		ret;
	t_obj	*obj;

	i = 0;
	while (var->obj_info[i])
		i++;
	if ((!BONUS && i != 4) || (BONUS && !(i == 4 || i == 5)))
		exit_error_parsing(error(PLANE_FORMAT_ERROR, line), NULL, var);
	obj = new_obj(PLANE, -1, -1, var);
	ret = fill_vertex(var->obj_info[2], obj->dir);
	ret += fill_rgb(var->obj_info[3], obj->color);
	ret += fill_coordinates(var->obj_info[1], obj->origin);
	if (BONUS && i == 5)
		ret += parse_checker(obj, var->obj_info[4]);
	if (check(obj, PLANE) == FAIL || ret)
		exit_error_parsing(error(PLANE_FORMAT_ERROR, line), NULL, var);
	obj->hit_object = &hit_plane;
	obj->get_uv_coord = &get_plane_uv;
	obj->shine_factor = 0.2;
	obj_add_back(&var->objs, obj);
}

void	fill_cylinder(t_parsing *var, char *line)
{
	int		i;
	t_obj	*obj;
	int		ret;

	i = 0;
	while (var->obj_info[i])
		i++;
	if ((!BONUS && i != 6) || (BONUS && !(i == 6 || i == 7)))
		exit_error_parsing(error(CYLINDER_FORMAT_ERROR, line), NULL, var);
	obj = new_obj(CYLINDER, ft_atof(var->obj_info[3]),
			ft_atof(var->obj_info[4]), var);
	ret = fill_vertex(var->obj_info[2], obj->dir);
	ret += fill_rgb(var->obj_info[5], obj->color);
	ret += fill_coordinates(var->obj_info[1], obj->origin);
	if (BONUS && i == 7)
		ret += parse_checker(obj, var->obj_info[6]);
	if (check(obj, CYLINDER) == FAIL || ret)
		exit_error_parsing(error(CYLINDER_FORMAT_ERROR, line), NULL, var);
	obj->hit_object = &hit_cylinder;
	obj->get_uv_coord = &get_cylinder_uv;
	obj->shine_factor = 0.3;
	obj_add_back(&var->objs, obj);
}

void	fill_disk(t_parsing *var, char *line)
{
	int		i;
	int		ret;
	t_obj	*obj;

	i = 0;
	while (var->obj_info[i])
		i++;
	if ((!BONUS && i != 5) || (BONUS && !(i == 5 || i == 6)))
		exit_error_parsing(error(DISK_FORMAT_ERROR, line), NULL, var);
	obj = new_obj(DISK, ft_atof(var->obj_info[3]), -1, var);
	ret = fill_coordinates(var->obj_info[1], obj->origin);
	ret += fill_vertex(var->obj_info[2], obj->dir);
	if (BONUS && i == 6)
		ret += parse_checker(obj, var->obj_info[5]);
	if (BONUS && var->obj_info[4] && var->obj_info[4][0] == '\"')
		parse_texture(var, obj, var->obj_info[4]);
	else
		ret += fill_rgb(var->obj_info[4], obj->color);
	if (check(obj, DISK) == FAIL || ret)
		exit_error_parsing(error(DISK_FORMAT_ERROR, line), NULL, var);
	obj->hit_object = &hit_disk;
	obj->get_uv_coord = &get_disk_uv;
	obj->shine_factor = 0.2;
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
