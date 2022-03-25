/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_matrix.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:41:15 by efrancon          #+#    #+#             */
/*   Updated: 2022/03/25 11:27:56 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

t_matrix3	rotate_x(double cos_theta)
{
	t_matrix3	rotation_x;
	double		sin_theta;

	sin_theta = sqrt(1 - (cos_theta * cos_theta));
	rotation_x.row_1 = create_vec3(1, 0, 0);
	rotation_x.row_2 = create_vec3(0, cos_theta, sin_theta);
	rotation_x.row_3 = create_vec3(0, -sin_theta, cos_theta);
	rotation_x.row_1 = get_normalized_vec3(rotation_x.row_1);
	rotation_x.row_2 = get_normalized_vec3(rotation_x.row_2);
	rotation_x.row_3 = get_normalized_vec3(rotation_x.row_3);
	return (rotation_x);
}

t_matrix3	rotate_y(double cos_theta)
{
	t_matrix3	rotation_y;
	double		sin_theta;

	sin_theta = sqrt(1 - (cos_theta * cos_theta));
	rotation_y.row_1 = create_vec3(cos_theta, 0, -sin_theta);
	rotation_y.row_2 = create_vec3(0, 1, 0);
	rotation_y.row_3 = create_vec3(sin_theta, 0, cos_theta);
	rotation_y.row_1 = get_normalized_vec3(rotation_y.row_1);
	rotation_y.row_2 = get_normalized_vec3(rotation_y.row_2);
	rotation_y.row_3 = get_normalized_vec3(rotation_y.row_3);
	return (rotation_y);
}

t_matrix3	rotate_z(double cos_theta)
{
	t_matrix3	rotation_z;
	double		sin_theta;

	sin_theta = sqrt(1 - (cos_theta * cos_theta));
	rotation_z.row_1 = create_vec3(cos_theta, sin_theta, 0);
	rotation_z.row_2 = create_vec3(-sin_theta, cos_theta, 0);
	rotation_z.row_3 = create_vec3(0, 0, 1);
	rotation_z.row_1 = get_normalized_vec3(rotation_z.row_1);
	rotation_z.row_2 = get_normalized_vec3(rotation_z.row_2);
	rotation_z.row_3 = get_normalized_vec3(rotation_z.row_3);
	return (rotation_z);
}

t_matrix3	create_rotation_matrix(t_vec3 obj_dir)
{
	t_matrix3	rotation_matrix;
	t_vec3		cos_theta;

	normalize_vec3(&obj_dir);
	cos_theta.coord[Z] = dot_vec2(
			create_vec2(obj_dir.coord[X], obj_dir.coord[Y]), create_vec2(0, 1));
	cos_theta.coord[X] = dot_vec2(
			create_vec2(obj_dir.coord[Y], obj_dir.coord[Z]), create_vec2(1, 0));
	cos_theta.coord[Y] = dot_vec2(
			create_vec2(obj_dir.coord[Z], obj_dir.coord[X]), create_vec2(0, 1));
	if (!get_norm_vec3(cos_theta))
	{
		cos_theta.coord[Z] = dot_vec2(create_vec2(obj_dir.coord[X],
					obj_dir.coord[Y]), create_vec2(1, 0));
		cos_theta.coord[X] = dot_vec2(create_vec2(obj_dir.coord[Y],
					obj_dir.coord[Z]), create_vec2(0, 1));
		cos_theta.coord[Y] = dot_vec2(create_vec2(obj_dir.coord[Z],
					obj_dir.coord[X]), create_vec2(0, 1));
	}
	rotation_matrix = mul_matrix3(
			rotate_x(cos_theta.coord[X]), rotate_y(cos_theta.coord[Y]));
	rotation_matrix = mul_matrix3(
			rotation_matrix, rotate_z(cos_theta.coord[Z]));
	return (rotation_matrix);
}
