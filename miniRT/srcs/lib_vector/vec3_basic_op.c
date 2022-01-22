#include "miniRT.h"

t_vector3	add_vec3(t_vector3 vector_1, t_vector3 vector_2)
{
	t_vector3	new_vector;

	new_vector.x = vector_1.x + vector_2.x;
	new_vector.y = vector_1.y + vector_2.y;
	new_vector.z = vector_1.z + vector_2.z;
	return (new_vector);
}

t_vector3	sub_vec3(t_vector3 vector_1, t_vector3 vector_2)
{
	t_vector3	new_vector;

	new_vector.x = vector_1.x - vector_2.x;
	new_vector.y = vector_1.y - vector_2.y;
	new_vector.z = vector_1.z - vector_2.z;
	return (new_vector);
}

t_vector3	mul_vec3(t_vector3 vector_1, t_vector3 vector_2)
{
	t_vector3	new_vector;

	new_vector.x = vector_1.x * vector_2.x;
	new_vector.y = vector_1.y * vector_2.y;
	new_vector.z = vector_1.z * vector_2.z;
	return (new_vector);
}

t_vector3	div_vec3(t_vector3 vector_1, t_vector3 vector_2)
{
	t_vector3	new_vector;

	new_vector.x = vector_1.x / vector_2.x;
	new_vector.y = vector_1.y / vector_2.y;
	new_vector.z = vector_1.z / vector_2.z;
	return (new_vector);
}

t_vector3	add_vec3_and_const(t_vector3 vector, float k)
{
	t_vector3	new_vector;

	new_vector.x = vector.x + k;
	new_vector.y = vector.y + k;
	new_vector.z = vector.z + k;
	return (new_vector);
}

t_vector3	sub_vec3_and_const(t_vector3 vector, float k)
{
	t_vector3	new_vector;

	new_vector.x = vector.x - k;
	new_vector.y = vector.y - k;
	new_vector.z = vector.z - k;
	return (new_vector);
}

t_vector3	mul_vec3_and_const(t_vector3 vector, float k)
{
	t_vector3	new_vector;

	new_vector.x = vector.x * k;
	new_vector.y = vector.y * k;
	new_vector.z = vector.z * k;
	return (new_vector);
}

t_vector3	add_vec3_and_const(t_vector3 vector, float k)
{
	t_vector3	new_vector;

	new_vector.x = vector.x / k;
	new_vector.y = vector.y / k;
	new_vector.z = vector.z / k;
	return (new_vector);
}
