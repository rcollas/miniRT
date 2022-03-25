/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_obj_bonus_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:44:49 by efrancon          #+#    #+#             */
/*   Updated: 2022/03/25 11:27:56 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

void	get_disk_info(t_parsing *var, char *line, int i)
{
	t_obj	*obj;
	int		ret;

	obj = new_obj(DISK, ft_atof(var->obj_info[3]), -1, var);
	obj_add_back(&var->objs, obj);
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
	obj->shine_factor = 0.3;
}

void	get_cone_info(t_parsing *var, char *line, int i)
{
	t_obj	*obj;
	int		ret;

	obj = new_obj(CONE, ft_atof(var->obj_info[3]),
			ft_atof(var->obj_info[4]), var);
	obj_add_back(&var->objs, obj);
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
}

void	get_sky_info(t_parsing *var, char *line, int i)
{
	t_obj	*obj;
	int		ret;

	obj = new_obj(SKY, ft_atof(var->obj_info[2]), -1, var);
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

void	get_square_info(t_parsing *var, char *line, int i)
{
	t_obj	*obj;
	int		ret;

	obj = new_obj(SQUARE, -1, ft_atof(var->obj_info[3]), var);
	obj_add_back(&var->objs, obj);
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
}
