#include "miniRT.h"

t_vec3	add_vec3(t_vec3 vector_1, t_vec3 vector_2)
{
	t_vec3	new_vector;

	new_vector.x = vector_1.x + vector_2.x;
	new_vector.y = vector_1.y + vector_2.y;
	new_vector.z = vector_1.z + vector_2.z;
	return (new_vector);
}

t_vec3	sub_vec3(t_vec3 vector_1, t_vec3 vector_2)
{
	t_vec3	new_vector;

	new_vector.x = vector_1.x - vector_2.x;
	new_vector.y = vector_1.y - vector_2.y;
	new_vector.z = vector_1.z - vector_2.z;
	return (new_vector);
}

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
