/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_init_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:35:43 by efrancon          #+#    #+#             */
/*   Updated: 2022/03/25 14:03:21 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

t_vec3	create_vec3(double x, double y, double z)
{
	t_vec3	new_vector;

	new_vector.coord[X] = x;
	new_vector.coord[Y] = y;
	new_vector.coord[Z] = z;
	return (new_vector);
}

void	copy_vec3(t_vec3 *dest, t_vec3 src)
{
	dest->coord[X] = src.coord[X];
	dest->coord[Y] = src.coord[Y];
	dest->coord[Z] = src.coord[Z];
}

t_vec3	convert_vec4_to_vec3(t_vec4 vector)
{
	t_vec3	new_vector;

	new_vector.coord[X] = vector.coord[X];
	new_vector.coord[Y] = vector.coord[Y];
	new_vector.coord[Z] = vector.coord[Z];
	return (new_vector);
}
