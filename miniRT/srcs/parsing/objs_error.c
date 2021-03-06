/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objs_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 11:05:50 by efrancon          #+#    #+#             */
/*   Updated: 2022/03/24 11:05:52 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	sphere_format_error(char *str)
{
	file_format_error();
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n\033[38;5;121m Expected:  [ID] sp   ", 2);
	error_coordinates();
	error_diameter();
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
	error_rgb();
	ft_putstr_fd("\033[0m\n\n", 2);
	return (CYLINDER_FORMAT_ERROR);
}
