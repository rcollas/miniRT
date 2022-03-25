/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_scene_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:43:38 by efrancon          #+#    #+#             */
/*   Updated: 2022/03/25 14:03:21 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

int	ambient_light_check(t_ambient_light *ambient_light)
{
	if (!is_in_range((double)0, (double)1, (double)ambient_light->intensity))
		return (FAIL);
	if (!is_valid_rgb(ambient_light->color))
		return (FAIL);
	return (SUCCESS);
}

int	camera_check(t_camera *camera)
{
	if (!is_valid_vertex(camera->dir))
		return (FAIL);
	if (!is_in_range((double)0, (double)180, (float)camera->fov))
		return (FAIL);
	return (SUCCESS);
}

int	diffuse_light_check(t_diffuse_light *diffuse_light)
{
	if (!is_in_range((double)0, (double)1, diffuse_light->intensity))
		return (FAIL);
	if (!is_valid_rgb(diffuse_light->color))
		return (FAIL);
	return (SUCCESS);
}
