#include "miniRT.h"

float	dot_product_vec3(t_vector3 vector_1, t_vector3 vector_2)
{
	return (vector_1.x * vector_2.x + vector_1.y * vector_2.y
		+ vector_2.z * vector_2.z);
}

t_vector3	cross_product_vec3(t_vector3 vector_1, t_vector3 vector_2)
{
	t_vector3	new_vector;

	new_vector.x = vector_1.y * vector_2.z - vector_1.z * vector_2.y;
	new_vector.y = vector_1.z * vector_2.x - vector_1.x * vector_2.z;
	new_vector.z = vector_1.x * vector_2.y - vector_1.y * vector_2.x;
	return (new_vector);
}

float	get_norm_vec3(t_vector3 vector)
{
	float	norm;

	norm = sqrt(powf(vector.x, 2) + powf(vector.y, 2) + powf(vector.z, 2));
	return (norm);
}

void	normalize_vec3(t_vector3 *vector)
{
	float	norm;

	norm = get_norm_vec3(*vector);
	vector->x = vector->x / norm;
	vector->y = vector->y / norm;
	vector->z = vector->z / norm;
}

t_vector4	convert_vec3_to_vec4(t_vector3 vector)
{
	t_vector4	new_vector;

	new_vector.x = vector.x;
	new_vector.y = vector.y;
	new_vector.z = vector.z;
	new_vector.t = 1;
	return (new_vector);
}

t_vector3	convert_vec4_to_vec3(t_vector4 vector)
{
	t_vector3	new_vector;

	new_vector.x = vector.x;
	new_vector.y = vector.y;
	new_vector.z = vector.z;
	return (new_vector);
}
