/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_scene_format_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:43:43 by efrancon          #+#    #+#             */
/*   Updated: 2022/03/25 14:03:21 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

int	ambient_light_format_error(char *str)
{
	file_format_error();
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n\033[38;5;121m Expected:  [ID] A   ", 2);
	error_intensity();
	error_rgb();
	ft_putstr_fd("\033[0m\n\n", 2);
	return (AMBIENT_LIGHT_FORMAT_ERROR);
}

int	camera_format_error(char *str)
{
	file_format_error();
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n\033[38;5;121m Expected:  [ID] C   ", 2);
	error_coordinates();
	error_vertex();
	ft_putstr_fd("[FOV] 0-180   ", 2);
	ft_putstr_fd("\033[0m\n\n", 2);
	return (CAMERA_FORMAT_ERROR);
}

int	diffuse_light_format_error(char *str)
{
	file_format_error();
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n\033[38;5;121m Expected:  [ID] L   ", 2);
	error_coordinates();
	error_intensity();
	if (BONUS)
		error_rgb();
	ft_putstr_fd("\033[0m\n\n", 2);
	return (DIFFUSE_LIGHT_FORMAT_ERROR);
}
