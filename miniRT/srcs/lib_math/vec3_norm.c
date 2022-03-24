/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_norm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 11:02:07 by efrancon          #+#    #+#             */
/*   Updated: 2022/03/24 11:02:08 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	get_norm2_vec3(t_vec3 vector)
{
	double	norm;

	norm = vector.coord[X] * vector.coord[X];
	norm += vector.coord[Y] * vector.coord[Y];
	norm += vector.coord[Z] * vector.coord[Z];
	return (norm);
}

double	get_norm_vec3(t_vec3 vector)
{
	return (sqrt(get_norm2_vec3(vector)));
}

void	normalize_vec3(t_vec3 *vector)
{
	double	norm_reciprocal;

	norm_reciprocal = 1 / get_norm_vec3(*vector);
	vector->coord[X] *= norm_reciprocal;
	vector->coord[Y] *= norm_reciprocal;
	vector->coord[Z] *= norm_reciprocal;
}

t_vec3	get_normalized_vec3(t_vec3 vector)
{
	normalize_vec3(&vector);
	return (vector);
}
