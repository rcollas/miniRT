#include "miniRT.h"

t_vec3	add_vec3_and_const(t_vec3 vector, double k)
{
	t_vec3	new_vector;

	new_vector.x = vector.x + k;
	new_vector.y = vector.y + k;
	new_vector.z = vector.z + k;
	return (new_vector);
}

t_vec3	sub_vec3_and_const(t_vec3 vector, double k)
{
	t_vec3	new_vector;

	new_vector.x = vector.x - k;
	new_vector.y = vector.y - k;
	new_vector.z = vector.z - k;
	return (new_vector);
}

t_vec3	mul_vec3_and_const(t_vec3 vector, double k)
{
	t_vec3	new_vector;

	new_vector.x = vector.x * k;
	new_vector.y = vector.y * k;
	new_vector.z = vector.z * k;
	return (new_vector);
}

t_vec3	div_vec3_and_const(t_vec3 vector, double k)
{
	t_vec3	new_vector;

	new_vector.x = vector.x / k;
	new_vector.y = vector.y / k;
	new_vector.z = vector.z / k;
	return (new_vector);
}
