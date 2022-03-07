#include "miniRT.h"

void	fill_sphere(t_parsing *var, char *line)
{
	int		i;
	int		ret;
	t_obj	*obj;

	i = 0;
	while (var->obj_info[i])
		i++;
	if (i != 4)
		ft_exit_parsing(error(SPHERE_FORMAT_ERROR, line), var);
	obj = new_obj(SPHERE, ft_atof(var->obj_info[2]), -1);
	ret = fill_coordinates(var->obj_info[1], obj->origin);
	ret += fill_rgb(var->obj_info[3], obj->color);
	if (check(obj, SPHERE) == FAIL || ret)
		ft_exit_parsing(error(SPHERE_FORMAT_ERROR, line), var);
	obj->hit_object = &hit_sphere;
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
	if (i != 4)
		ft_exit_parsing(error(PLANE_FORMAT_ERROR, line), var);
	obj = new_obj(PLANE, -1, -1);
	ret = fill_vertex(var->obj_info[2], obj->dir);
	ret += fill_rgb(var->obj_info[3], obj->color);
	ret += fill_coordinates(var->obj_info[1], obj->origin);
	if (check(obj, PLANE) == FAIL || ret)
		ft_exit_parsing(error(PLANE_FORMAT_ERROR, line), var);
	obj->hit_object = &hit_plane;
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
	if (i != 6)
		ft_exit_parsing(error(CYLINDER_FORMAT_ERROR, line), var);
	obj = new_obj(CYLINDER, ft_atof(var->obj_info[3]),
			ft_atof(var->obj_info[4]));
	ret = fill_vertex(var->obj_info[2], obj->dir);
	ret += fill_rgb(var->obj_info[5], obj->color);
	ret += fill_coordinates(var->obj_info[1], obj->origin);
	if (check(obj, CYLINDER) == FAIL || ret)
		ft_exit_parsing(error(CYLINDER_FORMAT_ERROR, line), var);
	obj->hit_object = &hit_cylinder;
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
	if (i != 5)
		ft_exit_parsing(error(DISK_FORMAT_ERROR, line), var);
	obj = new_obj(DISK, ft_atof(var->obj_info[3]), -1);
	ret = fill_coordinates(var->obj_info[1], obj->origin);
	ret += fill_vertex(var->obj_info[2], obj->dir);
	ret += fill_rgb(var->obj_info[4], obj->color);
	if (check(obj, DISK) == FAIL || ret)
		ft_exit_parsing(error(DISK_FORMAT_ERROR, line), var);
	obj->hit_object = &hit_disk;
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
