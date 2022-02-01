#include "../../incs/miniRT.h"

void	fill_sphere(t_parsing *var, char *line)
{
	int		i;
	t_obj	*obj;

	i = 0;
	while (var->obj_info[i])
		i++;
	if (i != 4)
	{
		error(SPHERE_FORMAT_ERROR, line);
		ft_exit_parsing(SPHERE_FORMAT_ERROR, var);
	}
	obj = new_obj(SPHERE, ft_atof(var->obj_info[2]), -1);
	fill_coordinates(var->obj_info[1], obj->origin);
	fill_rgb(var->obj_info[3], obj->color);
	if (check(obj, SPHERE) == FAIL)
	{
		error(SPHERE_FORMAT_ERROR, line);
		ft_exit_parsing(SPHERE_FORMAT_ERROR, var);
	}
	obj->hit_object = &hit_sphere;
	obj_add_back(&var->objs, obj);
}

void	fill_plan(t_parsing *var, char *line)
{
	int		i;
	t_obj	*obj;

	i = 0;
	while (var->obj_info[i])
		i++;
	if (i != 4)
	{
		error(PLAN_FORMAT_ERROR, line);
		ft_exit_parsing(PLAN_FORMAT_ERROR, var);
	}
	obj = new_obj(PLAN, -1, -1);
	fill_vertex(var->obj_info[2], obj->dir);
	fill_rgb(var->obj_info[3], obj->color);
	fill_coordinates(var->obj_info[1], obj->origin);
	if (check(obj, PLAN) == FAIL)
	{
		error(PLAN_FORMAT_ERROR, line);
		ft_exit_parsing(PLAN_FORMAT_ERROR, var);
	}
	obj->hit_object = &hit_plan;
	obj_add_back(&var->objs, obj);
}

void	fill_cylinder(t_parsing *var, char *line)
{
	int	i;
	t_obj	*obj;

	i = 0;
	while (var->obj_info[i])
		i++;
	if (i != 6)
	{
		error(CYLINDER_FORMAT_ERROR, line);
		ft_exit_parsing(CYLINDER_FORMAT_ERROR, var);
	}
	obj = new_obj(CYLINDER, ft_atof(var->obj_info[3]),
				  ft_atof(var->obj_info[4]));
	fill_vertex(var->obj_info[2], obj->dir);
	fill_rgb(var->obj_info[5], obj->color);
	fill_coordinates(var->obj_info[1], obj->origin);
	if (check(obj, CYLINDER) == FAIL)
	{
		error(CYLINDER_FORMAT_ERROR, line);
		ft_exit_parsing(CYLINDER_FORMAT_ERROR, var);
	}
	obj->hit_object = &hit_cylinder;
	obj_add_back(&var->objs, obj);
}

void	fill_obj(int type, t_parsing *var, char *line)
{
	if (type == SPHERE)
		fill_sphere(var, line);
	if (type == PLAN)
		fill_plan(var, line);
	if (type == CYLINDER)
		fill_cylinder(var, line);
}
