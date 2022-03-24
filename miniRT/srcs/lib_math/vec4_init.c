/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec4_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 11:02:38 by efrancon          #+#    #+#             */
/*   Updated: 2022/03/24 11:02:39 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec4	create_vec4(double x, double y, double z, double t)
{
	t_vec4	new_vector;

	new_vector.coord[X] = x;
	new_vector.coord[Y] = y;
	new_vector.coord[Z] = z;
	new_vector.coord[T] = t;
	return (new_vector);
}

t_vec4	convert_vec3_to_vec4(t_vec3 vector)
{
	t_vec4	new_vector;

	new_vector.coord[X] = vector.coord[X];
	new_vector.coord[Y] = vector.coord[Y];
	new_vector.coord[Z] = vector.coord[Z];
	new_vector.coord[T] = 1;
	return (new_vector);
}
