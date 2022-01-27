#include "miniRT.h"

t_vec4	create_vec4(double x, double y, double z, double t)
{
	t_vec4	new_vector;

	new_vector.x = x;
	new_vector.y = y;
	new_vector.z = z;
	new_vector.t = t;
	return (new_vector);
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
