/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_op1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 11:02:14 by efrancon          #+#    #+#             */
/*   Updated: 2022/03/24 11:02:15 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec3	add_vec3_and_const(t_vec3 vector, double k)
{
	t_vec3	new_vector;

	new_vector.coord[X] = vector.coord[X] + k;
	new_vector.coord[Y] = vector.coord[Y] + k;
	new_vector.coord[Z] = vector.coord[Z] + k;
	return (new_vector);
}

t_vec3	sub_vec3_and_const(t_vec3 vector, double k)
{
	t_vec3	new_vector;

	new_vector.coord[X] = vector.coord[X] - k;
	new_vector.coord[Y] = vector.coord[Y] - k;
	new_vector.coord[Z] = vector.coord[Z] - k;
	return (new_vector);
}

t_vec3	mul_vec3_and_const(t_vec3 vector, double k)
{
	t_vec3	new_vector;

	new_vector.coord[X] = vector.coord[X] * k;
	new_vector.coord[Y] = vector.coord[Y] * k;
	new_vector.coord[Z] = vector.coord[Z] * k;
	return (new_vector);
}

t_vec3	div_vec3_and_const(t_vec3 vector, double k)
{
	t_vec3	new_vector;

	new_vector.coord[X] = vector.coord[X] / k;
	new_vector.coord[Y] = vector.coord[Y] / k;
	new_vector.coord[Z] = vector.coord[Z] / k;
	return (new_vector);
}
