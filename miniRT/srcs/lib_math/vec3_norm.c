#include "miniRT.h"

float fast_inverse_sqrt( float number )
{
	long i;
	float x2, y;
	float threehalfs = 1.5F;

	x2 = number * 0.5F;
	y  = number;
	i  = * ( int * ) &y;
	i  = 0x5f3759df - ( i >> 1 );
	y  = * ( float * ) &i;
	y  = y * ( threehalfs - ( x2 * y * y ) );
	// y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed

	return (y);
}

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
	float	norm_reciprocal;

	// norm_reciprocal = 1 / get_norm_vec3(*vector);
	norm_reciprocal = fast_inverse_sqrt(get_norm2_vec3(*vector));
	vector->coord[X] *= norm_reciprocal;
	vector->coord[Y] *= norm_reciprocal;
	vector->coord[Z] *= norm_reciprocal;
}

t_vec3	get_normalized_vec3(t_vec3 vector)
{
	normalize_vec3(&vector);
	return (vector);
}
