/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 11:03:56 by efrancon          #+#    #+#             */
/*   Updated: 2022/03/24 11:03:57 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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
	if (!is_in_range((double)0, (double)180, (double)camera->fov))
		return (FAIL);
	return (SUCCESS);
}

int	diffuse_light_check(t_diffuse_light *diffuse_light)
{
	if (!is_in_range((double)0, (double)1, diffuse_light->intensity))
		return (FAIL);
	return (SUCCESS);
}
