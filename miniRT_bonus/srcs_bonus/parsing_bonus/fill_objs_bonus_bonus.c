/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_objs_bonus_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:44:06 by efrancon          #+#    #+#             */
/*   Updated: 2022/03/24 18:44:08 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

void	fill_disk(t_parsing *var, char *line)
{
	int		i;

	i = 0;
	while (var->obj_info[i])
		i++;
	if (BONUS)
	{
		if (!check_error_param_texture(i, 6))
			exit_error_parsing(error(DISK_FORMAT_ERROR, line), NULL, var);
	}
	else if (i != 6)
		exit_error_parsing(error(DISK_FORMAT_ERROR, line), NULL, var);
	get_disk_info(var, line, i);
}

void	fill_cone(t_parsing *var, char *line)
{
	int		i;

	i = 0;
	while (var->obj_info[i])
		i++;
	if (BONUS)
	{
		if (!check_error_param_texture(i, 6))
			exit_error_parsing(error(CONE_FORMAT_ERROR, line), NULL, var);
	}
	else if (i != 6)
		exit_error_parsing(error(CONE_FORMAT_ERROR, line), NULL, var);
	get_cone_info(var, line, i);
}

void	fill_sky(t_parsing *var, char *line)
{
	int		i;

	i = 0;
	while (var->obj_info[i])
		i++;
	if (BONUS)
	{
		if (!check_error_param_texture(i, 4))
			exit_error_parsing(error(SPHERE_FORMAT_ERROR, line), NULL, var);
	}
	else if (i != 4)
		exit_error_parsing(error(SPHERE_FORMAT_ERROR, line), NULL, var);
	get_sky_info(var, line, i);
}

void	fill_square(t_parsing *var, char *line)
{
	int		i;

	i = 0;
	while (var->obj_info[i])
		i++;
	if (BONUS)
	{
		if (!check_error_param_texture(i, 5))
			exit_error_parsing(error(SQUARE_FORMAT_ERROR, line), NULL, var);
	}
	else if (i != 5)
		exit_error_parsing(error(SQUARE_FORMAT_ERROR, line), NULL, var);
	get_square_info(var, line, i);
}
