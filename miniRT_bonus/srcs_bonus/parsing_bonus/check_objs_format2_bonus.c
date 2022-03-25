/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_objs_format2_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:43:32 by efrancon          #+#    #+#             */
/*   Updated: 2022/03/25 11:27:56 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

int	cone_format_error(char *str)
{
	file_format_error();
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n\033[38;5;121m Expected:  [ID] co   ", 2);
	error_coordinates();
	error_vertex();
	error_diameter();
	error_height();
	if (BONUS)
		format_bonus(NO_TEXTURE);
	else
		error_rgb();
	ft_putstr_fd("\033[0m\n\n", 2);
	return (CONE_FORMAT_ERROR);
}

int	square_format_error(char *str)
{
	file_format_error();
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n\033[38;5;121m Expected:  [ID] sq   ", 2);
	error_coordinates();
	error_vertex();
	error_height();
	if (BONUS)
		format_bonus(HAS_TEXTURE);
	else
		error_rgb();
	ft_putstr_fd("\033[0m\n\n", 2);
	return (SQUARE_FORMAT_ERROR);
}

int	disk_format_error(char *str)
{
	file_format_error();
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n\033[38;5;121m Expected:  [ID] di   ", 2);
	error_coordinates();
	error_vertex();
	error_diameter();
	ft_putstr_fd("[INNER_DIAMETER] 0.0   ", 2);
	if (BONUS)
		format_bonus(HAS_TEXTURE);
	else
		error_rgb();
	ft_putstr_fd("\033[0m\n\n", 2);
	return (DISK_FORMAT_ERROR);
}

int	sky_format_error(char *str)
{
	file_format_error();
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n\033[38;5;121m Expected:  [ID] sky   ", 2);
	error_coordinates();
	error_diameter();
	if (BONUS)
		format_bonus(HAS_TEXTURE);
	else
		error_rgb();
	ft_putstr_fd("\033[0m\n\n", 2);
	return (SPHERE_FORMAT_ERROR);
}
