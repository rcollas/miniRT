/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_list_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:45:11 by efrancon          #+#    #+#             */
/*   Updated: 2022/03/25 14:03:21 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

t_obj	*last_obj(t_obj *obj_list)
{
	if (!obj_list)
		return (NULL);
	while (obj_list)
	{
		if (obj_list->next == NULL)
			return (obj_list);
		obj_list = obj_list->next;
	}
	return (obj_list);
}

void	obj_add_back(t_obj **obj_list, t_obj *to_add)
{
	t_obj	*last;

	if (!obj_list || !to_add)
		return ;
	if (*obj_list)
	{
		last = last_obj(*obj_list);
		last->next = to_add;
	}
	else
		*obj_list = to_add;
}

t_obj	*new_obj(int type, double diameter, double height, t_parsing *var)
{
	t_obj	*obj;

	obj = (t_obj *)ft_calloc(1, sizeof(t_obj));
	if (!obj)
	{
		free(obj);
		exit_error_parsing(MALLOC_ERROR, "malloc() failed", var);
	}
	obj->type = type;
	obj->diameter = diameter;
	obj->radius = diameter * 0.5;
	obj->height = height;
	obj->inside_object = FALSE;
	obj->has_texture = FALSE;
	obj->texture->has_texture = FALSE;
	obj->bump_map->has_texture = FALSE;
	obj->inner_diameter = 0;
	obj->next = NULL;
	return (obj);
}
