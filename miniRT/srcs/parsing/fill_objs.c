#include "miniRT.h"

void	fill_sphere(t_parsing *var, char *line)
{
	int		i;
	int		ret;
	t_obj	*obj;

	i = 0;
	while (var->obj_info[i])
		i++;
	if (BONUS)
	{
		if (!check_error_param_texture(i, 4))
			exit_error_parsing(error(SPHERE_FORMAT_ERROR, line), NULL, var);
	}
	else if (i != 4)
		exit_error_parsing(error(SPHERE_FORMAT_ERROR, line), NULL, var);
	obj = new_obj(SPHERE, ft_atof(var->obj_info[2]), -1, var);
	ret = fill_coordinates(var->obj_info[1], obj->origin);
	if (BONUS)
		ret += parse_param_texture(var, obj, i, 4);
	else
		ret += fill_rgb(var->obj_info[3], obj->color);
	if (check(obj, SPHERE) == FAIL || ret)
		exit_error_parsing(error(SPHERE_FORMAT_ERROR, line), NULL, var);
	obj->hit_object = &hit_sphere;
	// obj->hit_object = &hit_hyperboloid;
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
	if (BONUS)
	{
		if (!check_error_param_texture(i, 4))
			exit_error_parsing(error(PLANE_FORMAT_ERROR, line), NULL, var);
	}
	else if (i != 4)
		exit_error_parsing(error(PLANE_FORMAT_ERROR, line), NULL, var);
	obj = new_obj(PLANE, -1, -1, var);
	ret = fill_vertex(var->obj_info[2], obj->dir);
	ret += fill_coordinates(var->obj_info[1], obj->origin);
	if (BONUS)
		ret += parse_param_texture(var, obj, i, 4);
	else
		ret += fill_rgb(var->obj_info[3], obj->color);
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
	if (BONUS)
	{
		if (!check_error_param_texture(i, 6))
			exit_error_parsing(error(CYLINDER_FORMAT_ERROR, line), NULL, var);
	}
	else if (i != 6)
		exit_error_parsing(error(CYLINDER_FORMAT_ERROR, line), NULL, var);
	obj = new_obj(CYLINDER, ft_atof(var->obj_info[3]),
			ft_atof(var->obj_info[4]), var);
	ret = fill_vertex(var->obj_info[2], obj->dir);
	ret += fill_coordinates(var->obj_info[1], obj->origin);
	if (BONUS)
		ret += parse_param_texture(var, obj, i, 6);
	else
		ret += fill_rgb(var->obj_info[5], obj->color);
	if (check(obj, CYLINDER) == FAIL || ret)
		exit_error_parsing(error(CYLINDER_FORMAT_ERROR, line), NULL, var);
	// obj->hit_object = &hit_cylinder;
	obj->hit_object = &hit_cone;
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
	if (BONUS)
	{
		if (!check_error_param_texture(i, 6))
			exit_error_parsing(error(DISK_FORMAT_ERROR, line), NULL, var);
	}
	else if (i != 6)
		exit_error_parsing(error(DISK_FORMAT_ERROR, line), NULL, var);
	obj = new_obj(DISK, ft_atof(var->obj_info[3]), -1, var);
	obj->inner_diameter = ft_atof(var->obj_info[4]);
	ret = fill_coordinates(var->obj_info[1], obj->origin);
	ret += fill_vertex(var->obj_info[2], obj->dir);
	if (BONUS)
		ret += parse_param_texture(var, obj, i, 6);
	else
		ret += fill_rgb(var->obj_info[5], obj->color);
	if (check(obj, DISK) == FAIL || ret)
		exit_error_parsing(error(DISK_FORMAT_ERROR, line), NULL, var);
	obj->hit_object = &hit_disk;
	obj->get_uv_coord = &get_disk_uv;
	obj->shine_factor = 0.2;
	obj_add_back(&var->objs, obj);
}

// void	fill_cone(t_parsing *var, char *line)
// {
// 	int		i;
// 	t_obj	*obj;
// 	int		ret;

// 	i = 0;
// 	while (var->obj_info[i])
// 		i++;
// 	if (BONUS)
// 	{
// 		if (!check_error_param_texture(i, 6))
// 			exit_error_parsing(error(CYLINDER_FORMAT_ERROR, line), NULL, var);
// 	}
// 	else if (i != 6)
// 		exit_error_parsing(error(CYLINDER_FORMAT_ERROR, line), NULL, var);
// 	obj = new_obj(CONE, ft_atof(var->obj_info[3]),
// 			ft_atof(var->obj_info[4]), var);
// 	ret = fill_vertex(var->obj_info[2], obj->dir);
// 	ret += fill_coordinates(var->obj_info[1], obj->origin);
// 	if (BONUS)
// 		ret += parse_param_texture(var, obj, i, 6);
// 	else
// 		ret += fill_rgb(var->obj_info[5], obj->color);
// 	if (check(obj, CYLINDER) == FAIL || ret)
// 		exit_error_parsing(error(CYLINDER_FORMAT_ERROR, line), NULL, var);
// 	obj->hit_object = &hit_cylinder;
// 	obj->get_uv_coord = &get_cylinder_uv;
// 	obj->shine_factor = 0.3;
// 	obj_add_back(&var->objs, obj);
// }

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
	// if (type == CONE)
	// 	fill_cone(var, line);
}
