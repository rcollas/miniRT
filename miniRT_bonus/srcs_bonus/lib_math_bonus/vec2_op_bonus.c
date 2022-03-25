/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2_op_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:35:38 by efrancon          #+#    #+#             */
/*   Updated: 2022/03/25 14:03:21 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

double	dot_vec2(t_vec2 vector_1, t_vec2 vector_2)
{
	return (vector_1.coord[X] * vector_2.coord[X]
		+ vector_1.coord[Y] * vector_2.coord[Y]);
}

double	get_norm_vec2(t_vec2 vector)
{
	double	norm;

	norm = vector.coord[X] * vector.coord[X];
	norm += vector.coord[Y] * vector.coord[Y];
	norm = sqrt(norm);
	return (norm);
}

void	normalize_vec2(t_vec2 *vector)
{
	double	norm_reciprocal;
	double	norm;

	norm_reciprocal = 0;
	norm = get_norm_vec2(*vector);
	if (norm > 0)
		norm_reciprocal = 1 / norm;
	vector->coord[X] *= norm_reciprocal;
	vector->coord[V] *= norm_reciprocal;
}

t_vec2	create_vec2(double x, double y)
{
	t_vec2	new_vector;

	new_vector.coord[X] = x;
	new_vector.coord[Y] = y;
	return (new_vector);
}
