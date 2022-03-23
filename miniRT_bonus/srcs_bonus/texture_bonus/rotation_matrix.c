#include "miniRT_bonus.h"

void	print_matrix3(t_matrix3 matrix)
{
	printf("row_1[x] = %f    row_1[y] = %f    row_1[z] = %f\n",
		matrix.row_1.coord[X], matrix.row_1.coord[Y], matrix.row_1.coord[Z]);
	printf("row_2[x] = %f    row_2[y] = %f    row_2[z] = %f\n",
		matrix.row_2.coord[X], matrix.row_2.coord[Y], matrix.row_2.coord[Z]);
	printf("row_3[x] = %f    row_3[y] = %f    row_3[z] = %f\n\n\n",
		matrix.row_3.coord[X], matrix.row_3.coord[Y], matrix.row_3.coord[Z]);
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

	return (new_matrix);
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

t_matrix3	rotate_x(double theta)
{
	t_matrix3	rotation_x;

	rotation_x.row_1 = create_vec3(1, 0, 0);
	rotation_x.row_2 = create_vec3(0, cos(theta), -sin(theta));
	rotation_x.row_3 = create_vec3(0, sin(theta), cos(theta));
	rotation_x.row_1 = get_normalized_vec3(rotation_x.row_1);
	rotation_x.row_2 = get_normalized_vec3(rotation_x.row_2);
	rotation_x.row_3 = get_normalized_vec3(rotation_x.row_3);
	return (rotation_x);
}

t_matrix3	rotate_y(double theta)
{
	t_matrix3	rotation_y;

	rotation_y.row_1 = create_vec3(cos(theta), 0, sin(theta));
	rotation_y.row_2 = create_vec3(0, 1, 0);
	rotation_y.row_3 = create_vec3(-sin(theta), 0, cos(theta));
	rotation_y.row_1 = get_normalized_vec3(rotation_y.row_1);
	rotation_y.row_2 = get_normalized_vec3(rotation_y.row_2);
	rotation_y.row_3 = get_normalized_vec3(rotation_y.row_3);
	return (rotation_y);
}

t_matrix3	rotate_z(double theta)
{
	t_matrix3	rotation_z;

	rotation_z.row_1 = create_vec3(cos(theta), -sin(theta), 0);
	rotation_z.row_2 = create_vec3(sin(theta), cos(theta), 0);
	rotation_z.row_3 = create_vec3(0, 0, 1);
	rotation_z.row_1 = get_normalized_vec3(rotation_z.row_1);
	rotation_z.row_2 = get_normalized_vec3(rotation_z.row_2);
	rotation_z.row_3 = get_normalized_vec3(rotation_z.row_3);
	return (rotation_z);
}

t_matrix3	create_rotation_matrix(t_vec3 obj_dir)
{
	t_matrix3	rotation_matrix;
	double		angle[3];
	t_vec3		vector[3];

	normalize_vec3(&obj_dir);
	vector[0] = create_vec3(0, 1, 0);
	vector[1] = create_vec3(obj_dir.coord[X], obj_dir.coord[Y], obj_dir.coord[Z]);
	vector[2] = cross_vec3(vector[0], vector[1]);
	normalize_vec3(&vector[2]);
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
	// if (vector[2].coord[X] < 1)
	// {
	// 	if (vector[2].coord[X] > -1)
	// 	{
	// 		angle[Y] = asin(vector[2].coord[X]);
	// 		angle[X] = atan2(-vector[2].coord[Y], vector[2].coord[Z]);
	// 		angle[Z] = atan2(-vector[1].coord[X], vector[0].coord[X]);
	// 	}
	// 	else
	// 	{
	// 		angle[Y] = -M_PI / 2;
	// 		angle[X] = -atan2(vector[0].coord[Y], vector[1].coord[Y]);
	// 		angle[Z] = 0;
	// 	}
	// }
	// else
	// {
	// 	angle[Y] = M_PI / 2;
	// 	angle[X] = atan2(vector[0].coord[Y], vector[1].coord[Y]);
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

	print_matrix3(rotation_matrix);
	// rotation_matrix = inverse_matrix3(rotation_matrix);

	t_vec3	test;
	test = mul_dir_and_matrix3(obj_dir, rotation_matrix);
	normalize_vec3(&test);
	// printf("TEST : %f  %f  %f\n", test.coord[X], test.coord[Y], test.coord[Z]);

	return (rotation_matrix);
}
