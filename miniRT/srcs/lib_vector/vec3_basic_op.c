#include "miniRT.h"

t_vec3	create_vec3(double x, double y, double z)
{
	t_vec3	new_vector;

	new_vector.x = x;
	new_vector.y = y;
	new_vector.z = z;
	return (new_vector);
}

t_vec4	create_vec4(double x, double y, double z, double t)
{
	t_vec4	new_vector;

	new_vector.x = x;
	new_vector.y = y;
	new_vector.z = z;
	new_vector.t = t;
	return (new_vector);
}

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
