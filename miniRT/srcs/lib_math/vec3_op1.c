#include "miniRT.h"

t_vec3	add_vec3_and_const(t_vec3 vector, float k)
{
	t_vec3	new_vector;

	new_vector.coord[X] = vector.coord[X] + k;
	new_vector.coord[Y] = vector.coord[Y] + k;
	new_vector.coord[Z] = vector.coord[Z] + k;
	return (new_vector);
}

t_vec3	sub_vec3_and_const(t_vec3 vector, float k)
{
	t_vec3	new_vector;

	new_vector.coord[X] = vector.coord[X] - k;
	new_vector.coord[Y] = vector.coord[Y] - k;
	new_vector.coord[Z] = vector.coord[Z] - k;
	return (new_vector);
}

t_vec3	mul_vec3_and_const(t_vec3 vector, float k)
{
	t_vec3	new_vector;

	new_vector.coord[X] = vector.coord[X] * k;
	new_vector.coord[Y] = vector.coord[Y] * k;
	new_vector.coord[Z] = vector.coord[Z] * k;
	return (new_vector);
}

t_vec3	div_vec3_and_const(t_vec3 vector, float k)
{
	t_vec3	new_vector;

	new_vector.coord[X] = vector.coord[X] / k;
	new_vector.coord[Y] = vector.coord[Y] / k;
	new_vector.coord[Z] = vector.coord[Z] / k;
	return (new_vector);
}
