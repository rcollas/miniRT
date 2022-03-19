#include "miniRT.h"

t_vec3	inverse_vec3(t_vec3 vector)
{
	t_vec3	new_vector;

	new_vector.coord[X] = -1 * vector.coord[X];
	new_vector.coord[Y] = -1 * vector.coord[Y];
	new_vector.coord[Z] = -1 * vector.coord[Z];
	return (new_vector);
}

double	dot_vec3(t_vec3 vector_1, t_vec3 vector_2)
{
	return (vector_1.coord[X] * vector_2.coord[X]
		+ vector_1.coord[Y] * vector_2.coord[Y]
		+ vector_1.coord[Z] * vector_2.coord[Z]);
}

t_vec3	cross_vec3(t_vec3 vector_1, t_vec3 vector_2)
{
	t_vec3	new_vector;

	new_vector.coord[X] = vector_1.coord[Y] * vector_2.coord[Z]
		- vector_1.coord[Z] * vector_2.coord[Y];
	new_vector.coord[Y] = vector_1.coord[Z] * vector_2.coord[X]
		- vector_1.coord[X] * vector_2.coord[Z];
	new_vector.coord[Z] = vector_1.coord[X] * vector_2.coord[Y]
		- vector_1.coord[Y] * vector_2.coord[X];
	return (new_vector);
}
