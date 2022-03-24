#include "miniRT_bonus.h"

static void	compute_matrix_row(t_vec3 *new_row, t_vec3 row, t_matrix3 matrix_2)
{
	new_row->coord[X] = row.coord[X] * matrix_2.row_1.coord[X]
		+ row.coord[Y] * matrix_2.row_2.coord[X]
		+ row.coord[Z] * matrix_2.row_3.coord[X];
	new_row->coord[Y] = row.coord[X] * matrix_2.row_1.coord[Y]
		+ row.coord[Y] * matrix_2.row_2.coord[Y]
		+ row.coord[Z] * matrix_2.row_3.coord[Y];
	new_row->coord[Z] = row.coord[X] * matrix_2.row_1.coord[Z]
		+ row.coord[Y] * matrix_2.row_2.coord[Z]
		+ row.coord[Z] * matrix_2.row_3.coord[Z];
}

t_matrix3	mul_matrix3(t_matrix3 matrix_1, t_matrix3 matrix_2)
{
	t_matrix3	new_matrix;

	compute_matrix_row(&new_matrix.row_1, matrix_1.row_1, matrix_2);
	compute_matrix_row(&new_matrix.row_2, matrix_1.row_2, matrix_2);
	compute_matrix_row(&new_matrix.row_3, matrix_1.row_3, matrix_2);
	new_matrix.row_1 = get_normalized_vec3(new_matrix.row_1);
	new_matrix.row_2 = get_normalized_vec3(new_matrix.row_2);
	new_matrix.row_3 = get_normalized_vec3(new_matrix.row_3);
	return (new_matrix);
}

t_vec3	mul_vec3_and_matrix4(t_vec3 vector, t_matrix4 matrix)
{
	t_vec4	tmp;
	t_vec3	new_vector;

	tmp.coord[X] = vector.coord[X] * matrix.row_1.coord[X]
		+ vector.coord[Y] * matrix.row_2.coord[X]
		+ vector.coord[Z] * matrix.row_3.coord[X] + matrix.row_4.coord[X];
	tmp.coord[Y] = vector.coord[X] * matrix.row_1.coord[Y]
		+ vector.coord[Y] * matrix.row_2.coord[Y]
		+ vector.coord[Z] * matrix.row_3.coord[Y] + matrix.row_4.coord[Y];
	tmp.coord[Z] = vector.coord[X] * matrix.row_1.coord[Z]
		+ vector.coord[Y] * matrix.row_2.coord[Z]
		+ vector.coord[Z] * matrix.row_3.coord[Z] + matrix.row_4.coord[Z];
	tmp.coord[T] = vector.coord[X] * matrix.row_1.coord[T]
		+ vector.coord[Y] * matrix.row_2.coord[T]
		+ vector.coord[Z] * matrix.row_3.coord[T] + matrix.row_4.coord[T];
	new_vector.coord[X] = tmp.coord[X] / tmp.coord[T];
	new_vector.coord[Y] = tmp.coord[Y] / tmp.coord[T];
	new_vector.coord[Z] = tmp.coord[Z] / tmp.coord[T];
	return (new_vector);
}

t_vec3	mul_dir_and_matrix4(t_vec3 vector, t_matrix4 matrix)
{
	t_vec3	new_vector;

	new_vector.coord[X] = vector.coord[X] * matrix.row_1.coord[X]
		+ vector.coord[Y] * matrix.row_2.coord[X]
		+ vector.coord[Z] * matrix.row_3.coord[X]
		+ matrix.row_4.coord[X];
	new_vector.coord[Y] = vector.coord[X] * matrix.row_1.coord[Y]
		+ vector.coord[Y] * matrix.row_2.coord[Y]
		+ vector.coord[Z] * matrix.row_3.coord[Y]
		+ matrix.row_4.coord[Y];
	new_vector.coord[Z] = vector.coord[X] * matrix.row_1.coord[Z]
		+ vector.coord[Y] * matrix.row_2.coord[Z]
		+ vector.coord[Z] * matrix.row_3.coord[Z]
		+ matrix.row_4.coord[Z];
	return (new_vector);
}

t_vec3	mul_dir_and_matrix3(t_vec3 vector, t_matrix3 matrix)
{
	t_vec3	new_vector;

	new_vector.coord[X] = vector.coord[X] * matrix.row_1.coord[X]
		+ vector.coord[Y] * matrix.row_2.coord[X]
		+ vector.coord[Z] * matrix.row_3.coord[X];
	new_vector.coord[Y] = vector.coord[X] * matrix.row_1.coord[Y]
		+ vector.coord[Y] * matrix.row_2.coord[Y]
		+ vector.coord[Z] * matrix.row_3.coord[Y];
	new_vector.coord[Z] = vector.coord[X] * matrix.row_1.coord[Z]
		+ vector.coord[Y] * matrix.row_2.coord[Z]
		+ vector.coord[Z] * matrix.row_3.coord[Z];
	return (new_vector);
}
