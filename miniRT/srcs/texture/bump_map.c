#include"miniRT.h"

// void	from_tangent_to_world_space(t_ray *hit, t_vec3 *new_hit_dir)
// {
// 	t_vec3		tangent;
// 	t_vec3		bitangent;
// 	t_matrix4	tbn_matrix;
// 	double		phi;
// 	double		radius;
// 	double		theta;
// 	// double		raw_u;

// 	radius = get_norm_vec3(hit->dir);
// 	theta = atan2(hit->dir.coord[Z], hit->dir.coord[X]);
// 	// theta = acos(hit->dir.coord[Y] / radius);
// 	// phi = atan2(hit->dir.coord[Z], hit->dir.coord[X]);
// 	phi = acos(hit->dir.coord[Y] / radius);
// 	tangent.coord[X] = -1 * sin(phi);
// 	tangent.coord[Y] = 0;
// 	tangent.coord[Z] = cos(phi);
// 	// tangent.coord[X] = cos(theta) * sin(phi) * hit->origin.coord[X] + sin(theta) * sin(phi) *hit->origin.coord[Y] + cos(phi) * hit->origin.coord[Z];
// 	// tangent.coord[Y] = -1 * sin(theta) * hit->origin.coord[X] + cos(theta) * hit->origin.coord[Y];
// 	// tangent.coord[Z] = cos(theta) * cos(phi) * hit->origin.coord[X] + sin(theta) * cos(phi) * hit->origin.coord[Y] - sin(phi) * hit->origin.coord[Z];
// 	// printf("tangent : x = %f y = %f z = %f\n", tangent.coord[X], tangent.coord[Y], tangent.coord[Z]);
// 	// bitangent = cross_vec3(normal_map, tangent);
// 	normalize_vec3(&tangent);
// 	bitangent = cross_vec3(tangent, hit->dir);
// 	tbn_matrix.row_1 = create_vec4(tangent.coord[X], bitangent.coord[X], normal_map.coord[X], 0);
// 	tbn_matrix.row_2 = create_vec4(tangent.coord[Y], bitangent.coord[Y], normal_map.coord[Y], 0);
// 	tbn_matrix.row_3 = create_vec4(tangent.coord[Z], bitangent.coord[Z], normal_map.coord[Z], 0);
// 	// tbn_matrix.row_1 = create_vec4(tangent.coord[X], tangent.coord[Y], tangent.coord[Z], 0);
// 	// tbn_matrix.row_2 = create_vec4(bitangent.coord[X], bitangent.coord[Y], bitangent.coord[Z], 0);
// 	// tbn_matrix.row_3 = create_vec4(normal_map.coord[X], normal_map.coord[Y], normal_map.coord[Z], 0);
// 	tbn_matrix.row_4 = create_vec4(0, 0, 0, 1);
// 	tbn_matrix.row_1 = get_normalized_vec4(tbn_matrix.row_1);
// 	tbn_matrix.row_2 = get_normalized_vec4(tbn_matrix.row_2);
// 	tbn_matrix.row_3 = get_normalized_vec4(tbn_matrix.row_3);
// 	// printf("%f %f %f\t", tbn_matrix.row_2.coord[X], tbn_matrix.row_2.coord[Y], tbn_matrix.row_2.coord[Z]);
// 	// printf("%f %f %f\t", tbn_matrix.row_1.coord[X], tbn_matrix.row_1.coord[Y], tbn_matrix.row_1.coord[Z]);
// 	// printf("%f %f %f\n", tbn_matrix.row_3.coord[X], tbn_matrix.row_3.coord[Y], tbn_matrix.row_3.coord[Z]);
// 	hit->dir = mul_vec3_and_matrix4(*new_hit_dir, tbn_matrix);
// }

void	from_tangent_to_world_space(t_ray *hit, t_vec3 *new_hit_dir)
{
	t_vec3		tangent;
	t_vec3		bitangent;
	t_matrix4	tbn_matrix;

	normalize_vec3(&hit->dir);
	tangent = cross_vec3(hit->dir, create_vec3(0.0, 1.0, 0.0));
	if (!get_norm_vec3(tangent))
		tangent = cross_vec3(hit->dir, create_vec3(0.0, 0.0, 1.0));
	normalize_vec3(&tangent);
	// bitangent = cross_vec3(hit->dir, tangent);
	bitangent = cross_vec3(tangent, hit->dir);
	normalize_vec3(&bitangent);
	// tbn_matrix.row_1 = create_vec4(tangent.coord[X], bitangent.coord[X], hit->dir.coord[X], 0);
	// tbn_matrix.row_2 = create_vec4(tangent.coord[Y], bitangent.coord[Y], hit->dir.coord[Y], 0);
	// tbn_matrix.row_3 = create_vec4(tangent.coord[Z], bitangent.coord[Z], hit->dir.coord[Z], 0);
	tbn_matrix.row_1 = create_vec4(tangent.coord[X], tangent.coord[Y], tangent.coord[Z], 0);
	tbn_matrix.row_2 = create_vec4(bitangent.coord[X], bitangent.coord[Y], bitangent.coord[Z], 0);
	tbn_matrix.row_3 = create_vec4(hit->dir.coord[X], hit->dir.coord[Y], hit->dir.coord[Z], 0);
	tbn_matrix.row_4 = create_vec4(0, 0, 0, 1);
	tbn_matrix.row_1 = get_normalized_vec4(tbn_matrix.row_1);
	tbn_matrix.row_2 = get_normalized_vec4(tbn_matrix.row_2);
	tbn_matrix.row_3 = get_normalized_vec4(tbn_matrix.row_3);
	hit->dir = mul_vec3_and_matrix4(*new_hit_dir, tbn_matrix);
}

void	apply_bump_map(t_ray *hit)
{
    t_vec3	normal_map;
	t_vec3	new_hit_dir;

    create_texture(hit, hit->obj->bump_map, &normal_map);
	new_hit_dir.coord[X] = normal_map.coord[X] * 2.0 - 1.0;
	new_hit_dir.coord[Y] = normal_map.coord[Y] * 2.0 - 1.0;
	new_hit_dir.coord[Z] = normal_map.coord[Z] * 2.0 - 1.0;
	from_tangent_to_world_space(hit, &new_hit_dir);
	normalize_vec3(&hit->dir);
}
