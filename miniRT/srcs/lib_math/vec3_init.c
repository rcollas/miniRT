#include "miniRT.h"

t_vec3	create_vec3(double x, double y, double z)
{
	t_vec3	new_vector;

	new_vector.x = x;
	new_vector.y = y;
	new_vector.z = z;
	return (new_vector);
}

void	copy_vec3(t_vec3 *dest, t_vec3 *src)
{
	dest->x = src->x;
	dest->y = src->y;
	dest->z = src->z;
}

t_vec3	convert_vec4_to_vec3(t_vec4 vector)
{
	t_vec3	new_vector;

	new_vector.x = vector.x;
	new_vector.y = vector.y;
	new_vector.z = vector.z;
	return (new_vector);
}
