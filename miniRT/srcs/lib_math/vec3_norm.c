#include "miniRT.h"

double	get_norm_vec3(t_vec3 vector)
{
	double	norm;

	norm = sqrt(powf(vector.x, 2) + powf(vector.y, 2) + powf(vector.z, 2));
	return (norm);
}

double	get_norm2_vec3(t_vec3 vector)
{
	double	norm;

	norm = powf(vector.x, 2) + powf(vector.y, 2) + powf(vector.z, 2);
	return (norm);
}

void	normalize_vec3(t_vec3 *vector)
{
	double	norm_reciprocal;

	norm_reciprocal = 1 / get_norm_vec3(*vector);
	vector->x *= norm_reciprocal;
	vector->y *= norm_reciprocal;
	vector->z *= norm_reciprocal;
}

t_vec3	get_normalized_vec3(t_vec3 vector)
{
	normalize_vec3(&vector);
	return (vector);
}
