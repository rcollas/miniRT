/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 11:01:51 by efrancon          #+#    #+#             */
/*   Updated: 2022/03/24 11:01:52 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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
	double	norm;

	norm = get_norm_vec2(*vector);
	vector->coord[X] /= norm;
	vector->coord[V] /= norm;
}
