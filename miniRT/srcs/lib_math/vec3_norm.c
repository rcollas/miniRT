#include "miniRT.h"

float	get_norm2_vec3(t_vec3 vector)
{
	float	norm;

	norm = vector.coord[X] * vector.coord[X]
		+ vector.coord[Y] * vector.coord[Y]
		+ vector.coord[Z] * vector.coord[Z];
	return (norm);
}

float	get_norm_vec3(t_vec3 vector)
{
	float	norm;

	norm = sqrt(get_norm2_vec3(vector));
	return (norm);
}

void	normalize_vec3(t_vec3 *vector)
{
	double	norm_reciprocal;

	norm_reciprocal = 1 / get_norm_vec3(*vector);
	vector->coord[X] *= norm_reciprocal;
	vector->coord[Y] *= norm_reciprocal;
	vector->coord[Z] *= norm_reciprocal;
}

t_vec3	get_normalized_vec3(t_vec3 vector)
{
	normalize_vec3(&vector);
	return (vector);
}
