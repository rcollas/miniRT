
void	get_cylinder_uv(t_ray hit, t_vec2 *uv)
{
	double	theta;
	double	raw_u;
	t_vec3	obj_dir;
	double	diagonal;

	diagonal = sqrt(4 * obj.radius * obj.radius + obj.height * obj.height) / 2;
	copy_vec3(&obj_dir, *hit.obj->dir);
	normalize_vec3(&obj_dir);
	if (obj_dir.coord[X] == 1 || obj_dir.coord[X] == -1)
		theta = atan2(hit.dir.coord[Y], hit.dir.coord[Z]);
	else if (obj_dir.coord[Z] == 1 || obj_dir.coord[Z] == -1)
		theta = atan2(hit.dir.coord[X], hit.dir.coord[Y]);
	else
		theta = atan2(hit.dir.coord[X], hit.dir.coord[Z]);
	raw_u = theta / (2 * M_PI);
	uv->coord[U] = 1 - (raw_u + 0.5);
	if (obj_dir.coord[X] == 1 || obj_dir.coord[X] == -1)
		uv->coord[V] = hit.origin.coord[X];
	else if (obj_dir.coord[Z] == 1 || obj_dir.coord[Z] == -1)
		uv->coord[V] = hit.origin.coord[Z];
	else
		uv->coord[V] = hit.origin.coord[Y];
}

void	from_world_to_tangent_space(t_ray *hit, t_vec3 new_hit_dir)
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
			tangent.coord[X], bitangent.coord[X], hit->dir.coord[X], 0);
	tbn_matrix.row_2 = create_vec4(
			tangent.coord[Y], bitangent.coord[Y], hit->dir.coord[Y], 0);
	tbn_matrix.row_3 = create_vec4(
			tangent.coord[Z], bitangent.coord[Z], hit->dir.coord[Z], 0);
	tbn_matrix.row_4 = create_vec4(0, 0, 0, 1);
	tbn_matrix.row_1 = get_normalized_vec4(tbn_matrix.row_1);
	tbn_matrix.row_2 = get_normalized_vec4(tbn_matrix.row_2);
	tbn_matrix.row_3 = get_normalized_vec4(tbn_matrix.row_3);
	hit->dir = mul_vec3_and_matrix4(new_hit_dir, tbn_matrix);
	// printf("%f  %f  %f\n", hit->dir.coord[X], hit->dir.coord[Y], hit->dir.coord[Z]);
}

void	rotate_hit_dir_x(t_ray *hit, t_obj obj)
{
	t_matrix3	rotation_matrix;
	t_vec3		unit_vector;
	double		theta;

	(void)obj;
	unit_vector = create_vec3(0, 1, 0);
	theta = dot_vec3(unit_vector, *obj.dir) / (get_norm_vec3(unit_vector) * get_norm_vec3(*obj.dir));
	theta = acos(theta);
	rotation_matrix.row_1 = create_vec3(1, 0, 0);
	rotation_matrix.row_2 = create_vec3(0, cos(theta), sin(theta));
	rotation_matrix.row_3 = create_vec3(0, -sin(theta), cos(theta));
	rotation_matrix.row_1 = get_normalized_vec3(rotation_matrix.row_1);
	rotation_matrix.row_2 = get_normalized_vec3(rotation_matrix.row_2);
	rotation_matrix.row_3 = get_normalized_vec3(rotation_matrix.row_3);
	hit->dir = mul_dir_and_matrix3(hit->dir, rotation_matrix);
	hit->origin = mul_dir_and_matrix3(hit->origin, rotation_matrix);
}

void	rotate_hit_dir_y(t_ray *hit, t_obj obj)
{
	t_matrix3	rotation_matrix;
	t_vec3		unit_vector;
	double		theta;

	(void)obj;
	unit_vector = create_vec3(0, 1, 0);
	theta = dot_vec3(unit_vector, *obj.dir) / (get_norm_vec3(unit_vector) * get_norm_vec3(*obj.dir));
	theta = acos(theta);
	rotation_matrix.row_1 = create_vec3(cos(theta), 0, -sin(theta));
	rotation_matrix.row_2 = create_vec3(0, 1, 0);
	rotation_matrix.row_3 = create_vec3(sin(theta), 0, cos(theta));
	rotation_matrix.row_1 = get_normalized_vec3(rotation_matrix.row_1);
	rotation_matrix.row_2 = get_normalized_vec3(rotation_matrix.row_2);
	rotation_matrix.row_3 = get_normalized_vec3(rotation_matrix.row_3);
	hit->dir = mul_dir_and_matrix3(hit->dir, rotation_matrix);
	hit->origin = mul_dir_and_matrix3(hit->origin, rotation_matrix);
}

void	rotate_hit_dir_z(t_ray *hit, t_obj obj)
{
	t_matrix3	rotation_matrix;
	t_vec3		unit_vector;
	double		theta;

	(void)obj;
	unit_vector = create_vec3(0, 1, 0);
	theta = dot_vec3(unit_vector, *obj.dir) / (get_norm_vec3(unit_vector) * get_norm_vec3(*obj.dir));
	theta = acos(theta);
	rotation_matrix.row_1 = create_vec3(cos(theta), sin(theta), 0);
	rotation_matrix.row_2 = create_vec3(-sin(theta), cos(theta), 0);
	rotation_matrix.row_3 = create_vec3(0, 0, 1);
	rotation_matrix.row_1 = get_normalized_vec3(rotation_matrix.row_1);
	rotation_matrix.row_2 = get_normalized_vec3(rotation_matrix.row_2);
	rotation_matrix.row_3 = get_normalized_vec3(rotation_matrix.row_3);
	hit->dir = mul_dir_and_matrix3(hit->dir, rotation_matrix);
	hit->origin = mul_dir_and_matrix3(hit->origin, rotation_matrix);
}

void	get_plane_uv(t_ray hit, t_vec2 *uv)
{
	t_vec3	obj_dir;

	copy_vec3(&obj_dir, *hit.obj->dir);
	if (obj_dir.coord[X] == 1 || obj_dir.coord[X] == -1)
	{
		uv->coord[U] = hit.origin.coord[Y];
		uv->coord[V] = hit.origin.coord[Z];
	}
	else if (obj_dir.coord[Z] == 1 || obj_dir.coord[Z] == -1)
	{
		uv->coord[U] = hit.origin.coord[X];
		uv->coord[V] = hit.origin.coord[Y];
	}
	else
	{
		uv->coord[U] = hit.origin.coord[X];
		uv->coord[V] = hit.origin.coord[Z];
	}
}

void	get_square_uv(t_ray hit, t_vec2 *uv)
{
	t_vec2	point;
	double	diagonal;

	diagonal = sqrt(hit.obj->height * hit.obj->height
			+ hit.obj->height + hit.obj->height);
	point = transform_point_in_obj_space(
			hit.origin, *hit.obj->origin, diagonal * 0.5, *hit.obj->dir);
	uv->coord[U] = point.coord[X] * 0.5 + 0.5;
	uv->coord[V] = point.coord[Y] * 0.5 + 0.5;
	if (hit.obj->dir->coord[Z] == 1 || hit.obj->dir->coord[X] == -1
		|| hit.obj->dir->coord[Y] == 1 || hit.obj->dir->coord[Y] == -1)
		uv->coord[U] = 1 - uv->coord[U];
	if (hit.obj->dir->coord[Y] == 1)
		uv->coord[V] = 1 - uv->coord[V];
}

// ROTATION ZYX :

	// if (vector[2].coord[X] < 1)
	// {
	// 	if (vector[2].coord[X] > -1)
	// 	{
	// 		angle[Y] = asin(-vector[2].coord[X]);
	// 		angle[Z] = atan2(vector[1].coord[X], vector[0].coord[X]);
	// 		angle[X] = atan2(vector[2].coord[Y], vector[2].coord[Z]);
	// 	}
	// 	else
	// 	{
	// 		angle[Y] = M_PI / 2;
	// 		angle[Z] = -atan2(-vector[1].coord[Z], vector[1].coord[Y]);
	// 		angle[X] = 0;
	// 	}
	// }
	// else
	// {
	// 	angle[Y] = -M_PI / 2;
	// 	angle[Z] = atan2(-vector[1].coord[Z], vector[1].coord[Y]);
	// 	angle[X] = 0;
	// }

t_matrix3	create_rotation_matrix(t_vec3 obj_dir)
{
	t_matrix3	rotation_matrix;
	double		angle[3];
	t_vec3		vector[3];

	normalize_vec3(&obj_dir);
	vector[0] = create_vec3(0, 0, 1);
	vector[1] = create_vec3(obj_dir.coord[X], obj_dir.coord[Y], obj_dir.coord[Z]);
	vector[2] = cross_vec3(vector[0], vector[1]);
	// normalize_vec3(&vector[2]);
	printf("vector[2] : %f  %f  %f\n", vector[2].coord[X], vector[2].coord[Y], vector[2].coord[Z]);
	if (!get_norm_vec3(vector[2]))
	{
		vector[0] = create_vec3(0, 0, 1);
		vector[2] = cross_vec3(vector[0], vector[1]);	
		normalize_vec3(&vector[2]);
	}
	vector[1] = get_normalized_vec3(cross_vec3(vector[2], vector[0]));
	if (vector[2].coord[X] < 1)
	{
		if (vector[2].coord[X] > -1)
		{
			angle[Y] = asin(vector[2].coord[X]);
			angle[X] = atan2(-vector[2].coord[Y], vector[2].coord[Z]);
			angle[Z] = atan2(-vector[1].coord[X], vector[0].coord[X]);
		}
		else
		{
			angle[Y] = -M_PI / 2;
			angle[X] = -atan2(vector[0].coord[Y], vector[1].coord[Y]);
			angle[Z] = 0;
		}
	}
	else
	{
		angle[Y] = M_PI / 2;
		angle[X] = atan2(vector[0].coord[Y], vector[1].coord[Y]);
		angle[Z] = 0;
	}
	// if (vector[0].coord[Z] < 1)
	// {
	// 	if (vector[0].coord[Z] > -1)
	// 	{
	// 		angle[Y] = asin(vector[0].coord[Z]);
	// 		angle[X] = atan2(-vector[1].coord[Z], vector[2].coord[Z]);
	// 		angle[Z] = atan2(-vector[0].coord[Y], vector[0].coord[X]);
	// 	}
	// 	else
	// 	{
	// 		angle[Y] = -M_PI / 2;
	// 		angle[X] = -atan2(vector[1].coord[X], vector[1].coord[Y]);
	// 		angle[Z] = 0;
	// 	}
	// }
	// else
	// {
	// 	angle[Y] = M_PI / 2;
	// 	angle[X] = atan2(vector[1].coord[X], vector[1].coord[Y]);
	// 	angle[Z] = 0;
	// }

	// printf("%f  %f  %f\n", angle[0], angle[1], angle[2]);

	rotation_matrix = mul_matrix3(rotate_x(angle[X]), rotate_y(angle[Y]));
	rotation_matrix.row_1 = get_normalized_vec3(rotation_matrix.row_1);
	rotation_matrix.row_2 = get_normalized_vec3(rotation_matrix.row_2);
	rotation_matrix.row_3 = get_normalized_vec3(rotation_matrix.row_3);
	rotation_matrix = mul_matrix3(rotation_matrix, rotate_z(angle[Z]));
	rotation_matrix.row_1 = get_normalized_vec3(rotation_matrix.row_1);
	rotation_matrix.row_2 = get_normalized_vec3(rotation_matrix.row_2);
	rotation_matrix.row_3 = get_normalized_vec3(rotation_matrix.row_3);

	// print_matrix3(rotation_matrix);
	// rotation_matrix = inverse_matrix3(rotation_matrix);

	t_vec3	test;
	test = mul_dir_and_matrix3(obj_dir, rotation_matrix);
	normalize_vec3(&test);
	// printf("TEST : %f  %f  %f\n", test.coord[X], test.coord[Y], test.coord[Z]);

	return (rotation_matrix);
}

t_matrix3	create_rotation_matrix(t_vec3 obj_dir)
{
	t_matrix3	rotation_matrix;
	double		angle[3];
	t_vec3		vector[3];

	vector[0] = create_vec3(1, 0, 0);
	vector[1] = create_vec3(obj_dir.coord[X], obj_dir.coord[Y], obj_dir.coord[Z]);
	vector[2] = cross_vec3(vector[0], vector[1]);
	if (!get_norm_vec3(vector[2]))
	{
		vector[0] = create_vec3(0, 1, 0);
		vector[2] = cross_vec3(vector[0], vector[1]);	
	}
	// printf("vector[2] : %f  %f  %f  |  norm = %f\n", vector[2].coord[X], vector[2].coord[Y], vector[2].coord[Z], get_norm_vec3(vector[2]));
	normalize_vec3(&vector[2]);
	vector[1] = get_normalized_vec3(cross_vec3(vector[2], vector[0]));
	if (vector[2].coord[X] < 1)
	{
		if (vector[2].coord[X] > -1)
			angle[X] = atan2(-vector[2].coord[Y], vector[2].coord[Z]);
		else
			angle[X] = -atan2(vector[0].coord[Y], vector[1].coord[Y]);
	}
	else
		angle[X] = atan2(vector[0].coord[Y], vector[1].coord[Y]);


	vector[0] = create_vec3(0, 1, 0);
	vector[1] = create_vec3(obj_dir.coord[X], obj_dir.coord[Y], obj_dir.coord[Z]);
	normalize_vec3(&vector[1]);
	vector[2] = cross_vec3(vector[0], vector[1]);
	// printf("vector[2] : %f  %f  %f\n", vector[2].coord[X], vector[2].coord[Y], vector[2].coord[Z]);
	if (!get_norm_vec3(vector[2]))
	{
		vector[0] = create_vec3(0, 0, 1);
		vector[2] = cross_vec3(vector[0], vector[1]);	
	}
	normalize_vec3(&vector[2]);
	vector[1] = get_normalized_vec3(cross_vec3(vector[2], vector[0]));
	if (vector[2].coord[X] < 1)
	{
		if (vector[2].coord[X] > -1)
			angle[Y] = asin(vector[2].coord[X]);
		else
			angle[Y] = -M_PI / 2;
	}
	else
		angle[Y] = M_PI / 2;
	
	vector[0] = create_vec3(0, 0, -1);
	vector[1] = create_vec3(obj_dir.coord[X], obj_dir.coord[Y], obj_dir.coord[Z]);
	normalize_vec3(&vector[1]);
	vector[2] = cross_vec3(vector[0], vector[1]);
	// printf("vector[2] : %f  %f  %f\n", vector[2].coord[X], vector[2].coord[Y], vector[2].coord[Z]);
	if (!get_norm_vec3(vector[2]))
	{
		vector[0] = create_vec3(1, 0, 0);
		vector[2] = cross_vec3(vector[0], vector[1]);	
	}
	normalize_vec3(&vector[2]);
	vector[1] = get_normalized_vec3(cross_vec3(vector[2], vector[0]));
	if (vector[2].coord[X] < 1)
	{
		if (vector[2].coord[X] > -1)
			angle[Z] = atan2(-vector[1].coord[X], vector[0].coord[X]);
		else
			angle[Z] = 0;
	}
	else
		angle[Z] = 0;

	// printf("%f  %f  %f\n", angle[0], angle[1], angle[2]);

	rotation_matrix = mul_matrix3(rotate_x(angle[X]), rotate_y(angle[Y]));
	rotation_matrix.row_1 = get_normalized_vec3(rotation_matrix.row_1);
	rotation_matrix.row_2 = get_normalized_vec3(rotation_matrix.row_2);
	rotation_matrix.row_3 = get_normalized_vec3(rotation_matrix.row_3);
	rotation_matrix = mul_matrix3(rotation_matrix, rotate_z(angle[Z]));
	rotation_matrix.row_1 = get_normalized_vec3(rotation_matrix.row_1);
	rotation_matrix.row_2 = get_normalized_vec3(rotation_matrix.row_2);
	rotation_matrix.row_3 = get_normalized_vec3(rotation_matrix.row_3);

	// print_matrix3(rotation_matrix);
	// rotation_matrix = inverse_matrix3(rotation_matrix);

	t_vec3	test;
	test = mul_dir_and_matrix3(obj_dir, rotation_matrix);
	normalize_vec3(&test);
	printf("TEST : %f  %f  %f\n", test.coord[X], test.coord[Y], test.coord[Z]);

	return (rotation_matrix);
}


t_matrix3	inverse_matrix3(t_matrix3 matrix)
{
	t_matrix3	new_matrix;

	new_matrix.row_1.coord[X] = matrix.row_1.coord[X];
	new_matrix.row_1.coord[Y] = matrix.row_2.coord[X];
	new_matrix.row_1.coord[Z] = matrix.row_3.coord[X];

	new_matrix.row_2.coord[X] = matrix.row_1.coord[Y];
	new_matrix.row_2.coord[Y] = matrix.row_2.coord[Y];
	new_matrix.row_2.coord[Z] = matrix.row_3.coord[Y];

	new_matrix.row_3.coord[X] = matrix.row_1.coord[Z];
	new_matrix.row_3.coord[Y] = matrix.row_2.coord[Z];
	new_matrix.row_3.coord[Z] = matrix.row_3.coord[Z];
	return (new_matrix);
}

void	get_square_uv(t_ray hit, t_vec2 *uv)
{
	t_vec2	point;
	double	diagonal;

	diagonal = sqrt(hit.obj->height * hit.obj->height
			+ hit.obj->height + hit.obj->height);
	point = transform_point_in_obj_space(
			hit.origin, *hit.obj->origin, diagonal * 0.5, *hit.obj->dir);
	uv->coord[U] = point.coord[X] * 0.5 + 0.5;
	uv->coord[V] = point.coord[Y] * 0.5 + 0.5;
	if (hit.obj->dir->coord[Z] == 1 || hit.obj->dir->coord[X] == -1
		|| hit.obj->dir->coord[Y] == 1 || hit.obj->dir->coord[Y] == -1)
		uv->coord[U] = 1 - uv->coord[U];
	if (hit.obj->dir->coord[Y] == 1)
		uv->coord[V] = 1 - uv->coord[V];
}

void	get_cylinder_uv(t_ray hit, t_vec2 *uv)
{
	double	theta;
	double	raw_u;
	t_vec3	obj_dir;
	double	diagonal;

	diagonal = sqrt(4 * obj.radius * obj.radius + obj.height * obj.height) / 2;
	copy_vec3(&obj_dir, *hit.obj->dir);
	normalize_vec3(&obj_dir);
	if (obj_dir.coord[X] == 1 || obj_dir.coord[X] == -1)
		theta = atan2(hit.dir.coord[Y], hit.dir.coord[Z]);
	else if (obj_dir.coord[Z] == 1 || obj_dir.coord[Z] == -1)
		theta = atan2(hit.dir.coord[X], hit.dir.coord[Y]);
	else
		theta = atan2(hit.dir.coord[X], hit.dir.coord[Z]);
	raw_u = theta / (2 * M_PI);
	uv->coord[U] = 1 - (raw_u + 0.5);
	if (obj_dir.coord[X] == 1 || obj_dir.coord[X] == -1)
		uv->coord[V] = hit.origin.coord[X];
	else if (obj_dir.coord[Z] == 1 || obj_dir.coord[Z] == -1)
		uv->coord[V] = hit.origin.coord[Z];
	else
		uv->coord[V] = hit.origin.coord[Y];
}

void	get_plane_uv(t_ray hit, t_vec2 *uv)
{
	t_vec3	obj_dir;

	copy_vec3(&obj_dir, *hit.obj->dir);
	if (obj_dir.coord[X] == 1 || obj_dir.coord[X] == -1)
	{
		uv->coord[U] = hit.origin.coord[Y];
		uv->coord[V] = hit.origin.coord[Z];
	}
	else if (obj_dir.coord[Z] == 1 || obj_dir.coord[Z] == -1)
	{
		uv->coord[U] = hit.origin.coord[X];
		uv->coord[V] = hit.origin.coord[Y];
	}
	else
	{
		uv->coord[U] = hit.origin.coord[X];
		uv->coord[V] = hit.origin.coord[Z];
	}
}

t_matrix3	mul_matrix3(t_matrix3 matrix_1, t_matrix3 matrix_2)
{
	t_matrix3	new_matrix;

	new_matrix.row_1.coord[X] = matrix_1.row_1.coord[X] * matrix_2.row_1.coord[X]
		+ matrix_1.row_1.coord[Y] * matrix_2.row_2.coord[X]
		+ matrix_1.row_1.coord[Z] * matrix_2.row_3.coord[X];
	new_matrix.row_1.coord[Y] = matrix_1.row_1.coord[X] * matrix_2.row_1.coord[Y]
		+ matrix_1.row_1.coord[Y] * matrix_2.row_2.coord[Y]
		+ matrix_1.row_1.coord[Z] * matrix_2.row_3.coord[Y];
	new_matrix.row_1.coord[Z] = matrix_1.row_1.coord[X] * matrix_2.row_1.coord[Z]
		+ matrix_1.row_1.coord[Y] * matrix_2.row_2.coord[Z]
		+ matrix_1.row_1.coord[Z] * matrix_2.row_3.coord[Z];

	new_matrix.row_2.coord[X] = matrix_1.row_2.coord[X] * matrix_2.row_1.coord[X]
		+ matrix_1.row_2.coord[Y] * matrix_2.row_2.coord[X]
		+ matrix_1.row_2.coord[Z] * matrix_2.row_3.coord[X];
	new_matrix.row_2.coord[Y] = matrix_1.row_2.coord[X] * matrix_2.row_1.coord[Y]
		+ matrix_1.row_2.coord[Y] * matrix_2.row_2.coord[Y]
		+ matrix_1.row_2.coord[Z] * matrix_2.row_3.coord[Y];
	new_matrix.row_2.coord[Z] = matrix_1.row_2.coord[X] * matrix_2.row_1.coord[Z]
		+ matrix_1.row_2.coord[Y] * matrix_2.row_2.coord[Z]
		+ matrix_1.row_2.coord[Z] * matrix_2.row_3.coord[Z];

	new_matrix.row_3.coord[X] = matrix_1.row_3.coord[X] * matrix_2.row_1.coord[X]
		+ matrix_1.row_3.coord[Y] * matrix_2.row_2.coord[X]
		+ matrix_1.row_3.coord[Z] * matrix_2.row_3.coord[X];
	new_matrix.row_3.coord[Y] = matrix_1.row_3.coord[X] * matrix_2.row_1.coord[Y]
		+ matrix_1.row_3.coord[Y] * matrix_2.row_2.coord[Y]
		+ matrix_1.row_3.coord[Z] * matrix_2.row_3.coord[Y];
	new_matrix.row_3.coord[Z] = matrix_1.row_3.coord[X] * matrix_2.row_1.coord[Z]
		+ matrix_1.row_3.coord[Y] * matrix_2.row_2.coord[Z]
		+ matrix_1.row_3.coord[Z] * matrix_2.row_3.coord[Z];

	new_matrix.row_1 = get_normalized_vec3(new_matrix.row_1);
	new_matrix.row_2 = get_normalized_vec3(new_matrix.row_2);
	new_matrix.row_3 = get_normalized_vec3(new_matrix.row_3);
	return (new_matrix);
}
