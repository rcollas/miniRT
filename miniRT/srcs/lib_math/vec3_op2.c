#include "miniRT.h"

t_vec3	add_vec3(t_vec3 vector_1, t_vec3 vector_2)
{
	t_vec3	new_vector;

	new_vector.coord[X] = vector_1.coord[X] + vector_2.coord[X];
	new_vector.coord[Y] = vector_1.coord[Y] + vector_2.coord[Y];
	new_vector.coord[Z] = vector_1.coord[Z] + vector_2.coord[Z];
	return (new_vector);
}

t_vec3	sub_vec3(t_vec3 vector_1, t_vec3 vector_2)
{
	t_vec3	new_vector;

	new_vector.coord[X] = vector_1.coord[X] - vector_2.coord[X];
	new_vector.coord[Y] = vector_1.coord[Y] - vector_2.coord[Y];
	new_vector.coord[Z] = vector_1.coord[Z] - vector_2.coord[Z];
	return (new_vector);
}

t_vec3	mul_vec3(t_vec3 vector_1, t_vec3 vector_2)
{
	t_vec3	new_vector;

	new_vector.coord[X] = vector_1.coord[X] * vector_2.coord[X];
	new_vector.coord[Y] = vector_1.coord[Y] * vector_2.coord[Y];
	new_vector.coord[Z] = vector_1.coord[Z] * vector_2.coord[Z];
	return (new_vector);
}
