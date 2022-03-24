/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:45:20 by efrancon          #+#    #+#             */
/*   Updated: 2022/03/24 18:45:21 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

int	parsing_error(int errnum, char *str)
{
	ft_putstr_fd("Error\n", 2);
	if (errnum == EXTENSION_ERROR)
		return (extension_error(str));
	if (errnum == ARG_NUMBER_ERROR)
		return (arg_nb_error());
	if (errnum == IS_DIR_ERROR)
		return (is_dir_error(str));
	if (errnum == FILE_ERROR)
		return (file_error(str));
	if (errnum == INCOMPLETE_FILE_ERROR)
		return (incomplete_file_error(str));
	return (0);
}

int	format_error(int errnum, char *str)
{
	if (errnum == AMBIENT_LIGHT_FORMAT_ERROR)
		return (ambient_light_format_error(str));
	if (errnum == CAMERA_FORMAT_ERROR)
		return (camera_format_error(str));
	if (errnum == DIFFUSE_LIGHT_FORMAT_ERROR)
		return (diffuse_light_format_error(str));
	if (errnum == SPHERE_FORMAT_ERROR)
		return (sphere_format_error(str));
	if (errnum == PLANE_FORMAT_ERROR)
		return (plane_format_error(str));
	if (errnum == CYLINDER_FORMAT_ERROR)
		return (cylinder_format_error(str));
	if (errnum == CONE_FORMAT_ERROR)
		return (cone_format_error(str));
	if (errnum == DISK_FORMAT_ERROR)
		return (disk_format_error(str));
	if (errnum == SQUARE_FORMAT_ERROR)
		return (square_format_error(str));
	if (errnum == SKY_FORMAT_ERROR)
		return (sky_format_error(str));
	return (0);
}

int	error(int errnum, char *str)
{
	int	ret;

	ft_putstr_fd("Error\n", 2);
	if (errnum == CLOSE_ERROR)
		return (close_error(str));
	if (errnum == READ_ERROR)
		return (read_error(str));
	if (errnum == STRJOIN_ERROR)
		return (strjoin_error());
	if (errnum == INVALID_TYPE_ERROR)
		return (invalid_type_error(str));
	ret = format_error(errnum, str);
	if (ret)
		return (ret);
	return (0);
}
