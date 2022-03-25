/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_objs_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:43:22 by efrancon          #+#    #+#             */
/*   Updated: 2022/03/25 14:03:21 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

int	sphere_check(t_obj *sphere)
{
	if (sphere->diameter <= 0)
		return (FAIL);
	if (!is_valid_rgb(sphere->color))
		return (FAIL);
	if (BONUS && sphere->has_texture == CHECKER
		&& !is_valid_rgb(sphere->color_checker))
		return (FAIL);
	return (SUCCESS);
}

int	plane_check(t_obj *plane)
{
	if (!is_valid_vertex(plane->dir))
		return (FAIL);
	if (!is_valid_rgb(plane->color))
		return (FAIL);
	if (BONUS && plane->has_texture == CHECKER
		&& !is_valid_rgb(plane->color_checker))
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
	if (BONUS && cylinder->has_texture == CHECKER
		&& !is_valid_rgb(cylinder->color_checker))
		return (FAIL);
	return (SUCCESS);
}

int	square_check(t_obj *square)
{
	if (!is_valid_vertex(square->dir))
		return (FAIL);
	if (square->height <= 0)
		return (FAIL);
	if (!is_valid_rgb(square->color))
		return (FAIL);
	if (BONUS && square->has_texture == CHECKER
		&& !is_valid_rgb(square->color_checker))
		return (FAIL);
	return (SUCCESS);
}

int	disk_check(t_obj *disk)
{
	if (!is_valid_vertex(disk->dir))
		return (FAIL);
	if (disk->diameter <= 0)
		return (FAIL);
	if (!is_valid_rgb(disk->color))
		return (FAIL);
	if (BONUS && disk->has_texture == CHECKER
		&& !is_valid_rgb(disk->color_checker))
		return (FAIL);
	return (SUCCESS);
}
