#include "miniRT.h"

_Bool	solve_quadratic_equation(
	double *coeff, double *roots, double *closest_hit)
{
	double	delta;

	delta = coeff[B] * coeff[B] - (4 * coeff[A] * coeff[C]);
	if (delta < 0)
		return (0);
	roots[0] = (-coeff[B] - (sqrt(delta))) / (2 * coeff[A]);
	roots[1] = (-coeff[B] + (sqrt(delta))) / (2 * coeff[A]);
	if (roots[1] < 0)
		return (FALSE);
	if (roots[0] > 0)
		*closest_hit = roots[0];
	else
		*closest_hit = roots[1];
	return (TRUE);
}

float fast_inverse_sqrt(float number)
{
	long	i;
	float	x2;
	float	y;
	float	threehalfs;
	
	threehalfs = 1.5F;
	x2 = number * 0.5F;
	y  = number;
	i  = * (int *) &y;
	i  = 0x5f3759df - (i >> 1);
	y  = * (float *) &i;
	y  = y * (threehalfs - (x2 * y * y));
	return (y);
}
