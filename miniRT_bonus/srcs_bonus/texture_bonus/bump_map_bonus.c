/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:40:50 by efrancon          #+#    #+#             */
/*   Updated: 2022/03/25 14:03:21 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"miniRT_bonus.h"

void	from_tangent_to_world_space(t_ray *hit, t_vec3 new_hit_dir)
{
	t_vec3		tangent;
	t_vec3		bitangent;
	t_matrix4	tbn_matrix;

	normalize_vec3(&hit->dir);
	tangent = cross_vec3(hit->dir, create_vec3(0.0, 1.0, 0.0));
	if (!get_norm_vec3(tangent))
		tangent = cross_vec3(hit->dir, create_vec3(0.0, 0.0, 1.0));
	normalize_vec3(&tangent);
	bitangent = cross_vec3(tangent, hit->dir);
	normalize_vec3(&bitangent);
	tbn_matrix.row_1 = create_vec4(
			tangent.coord[X], tangent.coord[Y], tangent.coord[Z], 0);
	tbn_matrix.row_2 = create_vec4(
			bitangent.coord[X], bitangent.coord[Y], bitangent.coord[Z], 0);
	tbn_matrix.row_3 = create_vec4(
			hit->dir.coord[X], hit->dir.coord[Y], hit->dir.coord[Z], 0);
	tbn_matrix.row_4 = create_vec4(0, 0, 0, 1);
	tbn_matrix.row_1 = get_normalized_vec4(tbn_matrix.row_1);
	tbn_matrix.row_2 = get_normalized_vec4(tbn_matrix.row_2);
	tbn_matrix.row_3 = get_normalized_vec4(tbn_matrix.row_3);
	hit->dir = mul_vec3_and_matrix4(new_hit_dir, tbn_matrix);
}

void	apply_bump_map(t_ray *hit)
{
	t_vec3	normal_map;
	t_vec3	new_hit_dir;

	create_texture(hit, hit->obj->bump_map, &normal_map);
	new_hit_dir.coord[X] = normal_map.coord[X] * 2.0 - 1.0;
	new_hit_dir.coord[Y] = normal_map.coord[Y] * 2.0 - 1.0;
	new_hit_dir.coord[Z] = normal_map.coord[Z] * 2.0 - 1.0;
	normalize_vec3(&new_hit_dir);
	from_tangent_to_world_space(hit, new_hit_dir);
	normalize_vec3(&hit->dir);
}
