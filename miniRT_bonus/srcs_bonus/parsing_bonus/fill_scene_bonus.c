/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_scene_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:44:18 by efrancon          #+#    #+#             */
/*   Updated: 2022/03/25 14:03:21 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

void	fill_ambient_light(
	t_parsing *parsing, t_ambient_light *ambient_light, char *line)
{
	int				i;
	int				ret;

	i = 0;
	while (parsing->obj_info[i])
		i++;
	if (i != 3 || parsing->ambient_light)
	{
		error(AMBIENT_LIGHT_FORMAT_ERROR, line);
		exit_error_parsing(AMBIENT_LIGHT_FORMAT_ERROR, NULL, parsing);
	}
	ambient_light->type = AMBIENT_LIGHT;
	ambient_light->intensity = ft_atof(parsing->obj_info[1]);
	ret = fill_rgb(parsing->obj_info[2], ambient_light->color);
	if (check(ambient_light, AMBIENT_LIGHT) == FAIL || ret)
	{
		error(AMBIENT_LIGHT_FORMAT_ERROR, line);
		exit_error_parsing(AMBIENT_LIGHT_FORMAT_ERROR, NULL, parsing);
	}
	parsing->ambient_light = TRUE;
}

void	fill_camera(t_parsing *parsing, t_camera *camera, char *line)
{
	int			i;
	int			ret;

	i = 0;
	while (parsing->obj_info[i])
		i++;
	if (i != 4 || parsing->camera)
	{
		error(CAMERA_FORMAT_ERROR, line);
		exit_error_parsing(CAMERA_FORMAT_ERROR, NULL, parsing);
	}
	camera->type = CAMERA;
	ret = fill_coordinates(parsing->obj_info[1], camera->origin);
	ret += fill_vertex(parsing->obj_info[2], camera->dir);
	camera->fov = ft_atoi(parsing->obj_info[3]);
	if (check(camera, CAMERA) == FAIL || ret)
	{
		error(CAMERA_FORMAT_ERROR, line);
		exit_error_parsing(CAMERA_FORMAT_ERROR, NULL, parsing);
	}
	if (camera->fov > 179.0)
		camera->fov = 179.0;
	camera->fov = camera->fov * M_PI / 180;
	parsing->camera = TRUE;
}

void	fill_scene(int type, t_parsing *var, char *line)
{
	if (type == AMBIENT_LIGHT)
		fill_ambient_light(var, var->scene->ambient_light, line);
	if (type == CAMERA)
		fill_camera(var, var->scene->camera, line);
	if (type == DIFFUSE_LIGHT)
		fill_diffuse_light(var, line);
}
