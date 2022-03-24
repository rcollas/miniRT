/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_norm_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:35:48 by efrancon          #+#    #+#             */
/*   Updated: 2022/03/24 18:35:57 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

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
	double	norm;

	norm_reciprocal = 0;
	norm = get_norm_vec3(*vector);
	if (norm > 0)
		norm_reciprocal = 1 / norm;
	vector->coord[X] *= norm_reciprocal;
	vector->coord[Y] *= norm_reciprocal;
	vector->coord[Z] *= norm_reciprocal;
}

t_vec3	get_normalized_vec3(t_vec3 vector)
{
	normalize_vec3(&vector);
	return (vector);
}
