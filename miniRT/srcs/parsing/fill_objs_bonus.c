#include "miniRT.h"

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

void	fill_cone(t_parsing *var, char *line)
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
			exit_error_parsing(error(CONE_FORMAT_ERROR, line), NULL, var);
	}
	else if (i != 6)
		exit_error_parsing(error(CONE_FORMAT_ERROR, line), NULL, var);
	obj = new_obj(CONE, ft_atof(var->obj_info[3]),
			ft_atof(var->obj_info[4]), var);
	ret = fill_vertex(var->obj_info[2], obj->dir);
	ret += fill_coordinates(var->obj_info[1], obj->origin);
	if (BONUS)
		ret += parse_param_texture(var, obj, i, 6);
	else
		ret += fill_rgb(var->obj_info[5], obj->color);
	if (check(obj, CONE) == FAIL || ret)
		exit_error_parsing(error(CONE_FORMAT_ERROR, line), NULL, var);
	obj->hit_object = &hit_cone;
	obj->get_uv_coord = &get_cylinder_uv;
	obj->shine_factor = 0.5;
	obj_add_back(&var->objs, obj);
}

void	fill_sky(t_parsing *var, char *line)
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
	obj = new_obj(SKY, ft_atof(var->obj_info[2]), -1, var);
	ret = fill_coordinates(var->obj_info[1], obj->origin);
	if (BONUS)
		ret += parse_param_texture(var, obj, i, 4);
	else
		ret += fill_rgb(var->obj_info[3], obj->color);
	if (check(obj, SPHERE) == FAIL || ret)
		exit_error_parsing(error(SPHERE_FORMAT_ERROR, line), NULL, var);
	obj->hit_object = &hit_sphere;
	obj->get_uv_coord = &get_sphere_uv;
	obj->shine_factor = 0.3;
	obj_add_back(&var->objs, obj);
}

void	fill_square(t_parsing *var, char *line)
{
	int		i;
	t_obj	*obj;
	int		ret;

	i = 0;
	while (var->obj_info[i])
		i++;
	if (BONUS)
	{
		if (!check_error_param_texture(i, 5))
			exit_error_parsing(error(SQUARE_FORMAT_ERROR, line), NULL, var);
	}
	else if (i != 5)
		exit_error_parsing(error(SQUARE_FORMAT_ERROR, line), NULL, var);
	obj = new_obj(SQUARE, -1, ft_atof(var->obj_info[3]), var);
	ret = fill_vertex(var->obj_info[2], obj->dir);
	ret += fill_coordinates(var->obj_info[1], obj->origin);
	if (BONUS)
		ret += parse_param_texture(var, obj, i, 5);
	else
		ret += fill_rgb(var->obj_info[4], obj->color);
	if (check(obj, SQUARE) == FAIL || ret)
		exit_error_parsing(error(SQUARE_FORMAT_ERROR, line), NULL, var);
	obj->hit_object = &hit_square;
	obj->get_uv_coord = &get_square_uv;
	obj->shine_factor = 0.3;
	obj_add_back(&var->objs, obj);
}
