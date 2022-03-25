/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_obj_info_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:44:57 by efrancon          #+#    #+#             */
/*   Updated: 2022/03/25 11:27:56 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

void	get_cylinder_info(t_parsing *var, char *line, int i)
{
	t_obj	*obj;
	int		ret;

	obj = new_obj(CYLINDER, ft_atof(var->obj_info[3]),
			ft_atof(var->obj_info[4]), var);
	obj_add_back(&var->objs, obj);
	ret = fill_vertex(var->obj_info[2], obj->dir);
	ret += fill_coordinates(var->obj_info[1], obj->origin);
	if (BONUS)
		ret += parse_param_texture(var, obj, i, 6);
	else
		ret += fill_rgb(var->obj_info[5], obj->color);
	if (check(obj, CYLINDER) == FAIL || ret)
		exit_error_parsing(error(CYLINDER_FORMAT_ERROR, line), NULL, var);
	obj->hit_object = &hit_cylinder;
	obj->get_uv_coord = &get_cylinder_uv;
	obj->shine_factor = 0.3;
}

void	get_plane_info(t_parsing *var, char *line, int i)
{
	t_obj	*obj;
	int		ret;

	obj = new_obj(PLANE, -1, -1, var);
	obj_add_back(&var->objs, obj);
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
}

void	get_sphere_info(t_parsing *var, char *line, int i)
{
	t_obj	*obj;
	int		ret;

	obj = new_obj(SPHERE, ft_atof(var->obj_info[2]), -1, var);
	obj_add_back(&var->objs, obj);
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
}
