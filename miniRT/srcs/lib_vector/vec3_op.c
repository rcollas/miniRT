#include "miniRT.h"

double	dot_product_vec3(t_vec3 vector_1, t_vec3 vector_2)
{
	return (vector_1.x * vector_2.x + vector_1.y * vector_2.y
		+ vector_1.z * vector_2.z);
}

t_vec3	cross_product_vec3(t_vec3 vector_1, t_vec3 vector_2)
{
	t_vec3	new_vector;

	new_vector.x = vector_1.y * vector_2.z - vector_1.z * vector_2.y;
	new_vector.y = vector_1.z * vector_2.x - vector_1.x * vector_2.z;
	new_vector.z = vector_1.x * vector_2.y - vector_1.y * vector_2.x;
	return (new_vector);
}

double	get_norm_vec3(t_vec3 vector)
{
	double	norm;

	norm = sqrt(powf(vector.x, 2) + powf(vector.y, 2) + powf(vector.z, 2));
	return (norm);
}

double	get_norm2_vec3(t_vec3 vector)
{
	double	norm;

	norm = powf(vector.x, 2) + powf(vector.y, 2) + powf(vector.z, 2);
	return (norm);
}

void	normalize_vec3(t_vec3 *vector)
{
	double	norm_reciprocal;

	norm_reciprocal = 1 / get_norm_vec3(*vector);
	vector->x *= norm_reciprocal;
	vector->y *= norm_reciprocal;
	vector->z *= norm_reciprocal;
}

t_vec3	get_normalized_vec3(t_vec3 vector)
{
	normalize_vec3(&vector);
	return (vector);
}

t_vec4	convert_vec3_to_vec4(t_vec3 vector)
{
	t_vec4	new_vector;

	new_vector.x = vector.x;
	new_vector.y = vector.y;
	new_vector.z = vector.z;
	new_vector.t = 1;
	return (new_vector);
}

t_vec3	convert_vec4_to_vec3(t_vec4 vector)
{
	t_vec3	new_vector;

	new_vector.x = vector.x;
	new_vector.y = vector.y;
	new_vector.z = vector.z;
	return (new_vector);
}

void	copy_vec3(t_vec3 *dest, t_vec3 *src)
{
	dest->x = src->x;
	dest->y = src->y;
	dest->z = src->z;
}
