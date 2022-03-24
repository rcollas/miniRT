/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_objs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 11:03:51 by efrancon          #+#    #+#             */
/*   Updated: 2022/03/24 11:03:52 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	sphere_check(t_obj *sphere)
{
	if (sphere->diameter <= 0)
		return (FAIL);
	if (!is_valid_rgb(sphere->color))
		return (FAIL);
	return (SUCCESS);
}

int	plane_check(t_obj *plane)
{
	if (!is_valid_vertex(plane->dir))
		return (FAIL);
	if (!is_valid_rgb(plane->color))
		return (FAIL);
	return (SUCCESS);
}

int	cylinder_check(t_obj *cylinder)
{
	if (!is_valid_vertex(cylinder->dir))
		return (FAIL);
	if (cylinder->diameter <= 0)
		return (FAIL);
	if (cylinder->height <= 0)
		return (FAIL);
	if (!is_valid_rgb(cylinder->color))
		return (FAIL);
	return (SUCCESS);
}
