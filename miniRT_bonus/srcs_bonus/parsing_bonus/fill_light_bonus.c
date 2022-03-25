/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_light_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:44:01 by efrancon          #+#    #+#             */
/*   Updated: 2022/03/25 14:03:21 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

t_diffuse_light	*ft_realloc(t_parsing *parsing, t_diffuse_light *ptr)
{
	t_diffuse_light	*new_ptr;
	int				i;

	i = -1;
	if (parsing->light_nb == 1)
	{
		new_ptr = (t_diffuse_light *)ft_calloc(sizeof(t_diffuse_light), 1);
		if (!new_ptr)
			exit_error_parsing(MALLOC_ERROR, "malloc() failed", parsing);
	}
	else
	{
		new_ptr = ft_calloc(sizeof(t_diffuse_light), parsing->light_nb);
		if (!new_ptr)
			exit_error_parsing(MALLOC_ERROR, "malloc() failed", parsing);
		while (ptr && ++i < parsing->light_nb)
		{
			copy_vec3(new_ptr[i].color, *ptr[i].color);
			copy_vec3(new_ptr[i].coord, *ptr[i].coord);
			new_ptr[i].type = ptr[i].type;
			new_ptr[i].intensity = ptr[i].intensity;
		}
		free(ptr);
	}
	return (new_ptr);
}

void	get_light_info(t_parsing *parsing, int j, char *line, int i)
{
	int	ret;

	parsing->scene->diffuse_light = ft_realloc(parsing,
			parsing->scene->diffuse_light);
	parsing->scene->diffuse_light[j].type = DIFFUSE_LIGHT;
	ret = fill_coordinates(parsing->obj_info[1],
			parsing->scene->diffuse_light[j].coord);
	if (i == 4)
		ret += fill_rgb(parsing->obj_info[3],
				parsing->scene->diffuse_light[j].color);
	else
		copy_vec3(parsing->scene->diffuse_light[j].color,
			create_vec3(255, 255, 255));
	parsing->scene->diffuse_light[j].intensity = ft_atof(parsing->obj_info[2]);
	if (check(&parsing->scene->diffuse_light[j], DIFFUSE_LIGHT) == FAIL || ret)
	{
		ft_free(parsing->scene->diffuse_light);
		error(DIFFUSE_LIGHT_FORMAT_ERROR, line);
		exit_error_parsing(DIFFUSE_LIGHT_FORMAT_ERROR, NULL, parsing);
	}
	parsing->diffuse_light = TRUE;
}

void	fill_diffuse_light(t_parsing *parsing, char *line)
{
	int	i;
	int	j;

	i = 0;
	j = parsing->light_nb;
	parsing->light_nb++;
	while (parsing->obj_info[i])
		i++;
	if (i != 3 && i != 4)
	{
		ft_free(parsing->scene->diffuse_light);
		error(DIFFUSE_LIGHT_FORMAT_ERROR, line);
		exit_error_parsing(DIFFUSE_LIGHT_FORMAT_ERROR, NULL, parsing);
	}
	get_light_info(parsing, j, line, i);
}
