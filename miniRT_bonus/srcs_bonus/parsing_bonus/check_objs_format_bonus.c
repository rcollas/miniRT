/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_objs_format_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:43:26 by efrancon          #+#    #+#             */
/*   Updated: 2022/03/25 11:27:56 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

int	sphere_format_error(char *str)
{
	file_format_error();
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n\033[38;5;121m Expected:  [ID] sp   ", 2);
	error_coordinates();
	error_diameter();
	if (BONUS)
		format_bonus(HAS_TEXTURE);
	else
		error_rgb();
	ft_putstr_fd("\033[0m\n\n", 2);
	return (SPHERE_FORMAT_ERROR);
}

int	plane_format_error(char *str)
{
	file_format_error();
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n\033[38;5;121m Expected:  [ID] pl   ", 2);
	error_coordinates();
	error_vertex();
	if (BONUS)
		format_bonus(NO_TEXTURE);
	else
		error_rgb();
	ft_putstr_fd("\033[0m\n\n", 2);
	return (PLANE_FORMAT_ERROR);
}

int	cylinder_format_error(char *str)
{
	file_format_error();
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n\033[38;5;121m Expected:  [ID] cy   ", 2);
	error_coordinates();
	error_vertex();
	error_diameter();
	error_height();
	if (BONUS)
		format_bonus(HAS_TEXTURE);
	else
		error_rgb();
	ft_putstr_fd("\033[0m\n\n", 2);
	return (CYLINDER_FORMAT_ERROR);
}
