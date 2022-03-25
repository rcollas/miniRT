/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_list_to_tab_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:43:47 by efrancon          #+#    #+#             */
/*   Updated: 2022/03/25 14:03:21 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

void	copy_texture(t_image *dest, t_image *src)
{
	dest->img_ptr = src->img_ptr;
	dest->addr = src->addr;
	dest->width = src->width;
	dest->height = src->height;
	dest->endian = src->endian;
	dest->bpp = src->bpp;
	dest->line_len = src->line_len;
	dest->has_texture = src->has_texture;
}

void	copy_content(t_obj *dest, t_obj *src, int obj_nb)
{
	int	i;

	i = 0;
	while (src)
	{
		dest[i].type = src->type;
		copy_vec3(dest[i].origin, *src->origin);
		copy_vec3(dest[i].dir, *src->dir);
		copy_vec3(dest[i].color, *src->color);
		copy_vec3(dest[i].color_checker, *src->color_checker);
		dest[i].diameter = src->diameter;
		dest[i].radius = src->radius;
		dest[i].inner_diameter = src->inner_diameter;
		dest[i].height = src->height;
		dest[i].hit_object = src->hit_object;
		dest[i].get_uv_coord = src->get_uv_coord;
		dest[i].shine_factor = src->shine_factor;
		dest->obj_nb = obj_nb;
		dest[i].inside_object = src->inside_object;
		copy_texture(dest[i].texture, src->texture);
		copy_texture(dest[i].bump_map, src->bump_map);
		dest[i].has_texture = src->has_texture;
		i++;
		src = src->next;
	}
}

int	list_len(t_obj *obj)
{
	int	i;

	i = 0;
	while (obj)
	{
		i++;
		obj = obj->next;
	}
	return (i);
}

t_obj	*list_to_tab(t_obj *obj, t_parsing *parsing_var)
{
	int		i;
	int		obj_nb;
	t_obj	*obj_tab;

	i = 0;
	obj_nb = list_len(obj);
	obj_tab = (t_obj *)ft_calloc(obj_nb, sizeof(t_obj));
	if (!obj_tab)
	{
		exit_error_parsing_end(
			MALLOC_ERROR, "malloc failed()", parsing_var, NO_DESTROY_TEXTURE);
	}
	copy_content(obj_tab, obj, obj_nb);
	free_list(obj);
	return (obj_tab);
}
