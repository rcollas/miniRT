#include "miniRT.h"

t_vec3	mul_vec3_and_matrix4(t_vec3 vector, t_matrix4 matrix)
{
	t_vec4	tmp;
	t_vec3	new_vector;

	tmp.x = vector.x * matrix.row_1.x + vector.y * matrix.row_2.x + vector.z * matrix.row_3.x + matrix.row_4.x;
	tmp.y = vector.x * matrix.row_1.y + vector.y * matrix.row_2.y + vector.z * matrix.row_3.y + matrix.row_4.y;
	tmp.z = vector.x * matrix.row_1.z + vector.y * matrix.row_2.z + vector.z * matrix.row_3.z + matrix.row_4.z;
	tmp.t = vector.x * matrix.row_1.t + vector.y * matrix.row_2.t + vector.z * matrix.row_3.t + matrix.row_4.t;
	new_vector.x = tmp.x / tmp.t;
	new_vector.y = tmp.y / tmp.t;
	new_vector.z = tmp.z / tmp.t;
	// printf("x = %f | y = %f | z = %f | t = %f\n", new_vector.x, new_vector.y, new_vector.z, new_vector.t);
	return (new_vector);
}

t_vec3	mul_dir_and_matrix4(t_vec3 vector, t_matrix4 matrix)
{
	t_vec3	new_vector;

	new_vector.x = vector.x * matrix.row_1.x + vector.y * matrix.row_2.x + vector.z * matrix.row_3.x + matrix.row_4.x;
	new_vector.y = vector.x * matrix.row_1.y + vector.y * matrix.row_2.y + vector.z * matrix.row_3.y + matrix.row_4.y;
	new_vector.z = vector.x * matrix.row_1.z + vector.y * matrix.row_2.z + vector.z * matrix.row_3.z + matrix.row_4.z;
	// printf("x = %f | y = %f | z = %f | t = %f\n", new_vector.x, new_vector.y, new_vector.z, new_vector.t);
	return (new_vector);
}
