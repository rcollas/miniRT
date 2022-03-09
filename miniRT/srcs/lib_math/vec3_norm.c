#include "miniRT.h"

double	get_norm2_vec3(t_vec3 vector)
{
	double	norm;

	norm = vector.coord[X] * vector.coord[X];
	norm += vector.coord[Y] * vector.coord[Y];
	norm += vector.coord[Z] * vector.coord[Z];
	return (norm);
}

double	get_norm_vec3(t_vec3 vector)
{
	double	norm;

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

double	get_norm2_vec4(t_vec4 vector)
{
	double	norm;

	norm = vector.coord[X] * vector.coord[X];
	norm += vector.coord[Y] * vector.coord[Y];
	norm += vector.coord[Z] * vector.coord[Z];
	norm += vector.coord[T] * vector.coord[T];
	return (norm);
}

double	get_norm_vec4(t_vec4 vector)
{
	double	norm;

	norm = sqrt(get_norm2_vec4(vector));
	return (norm);
}

void	normalize_vec4(t_vec4 *vector)
{
	double	norm_reciprocal;

	norm_reciprocal = 1 / get_norm_vec4(*vector);
	vector->coord[X] *= norm_reciprocal;
	vector->coord[Y] *= norm_reciprocal;
	vector->coord[Z] *= norm_reciprocal;
	vector->coord[T] *= norm_reciprocal;
}

t_vec4	get_normalized_vec4(t_vec4 vector)
{
	normalize_vec4(&vector);
	return (vector);
}
