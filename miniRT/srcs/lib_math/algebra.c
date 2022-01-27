#include "miniRT.h"

int	resolve_quadratic_equation(double a, double b, double c, double ret[2])
{
	double	delta;

	delta = b * b - (4 * a * c);
	if (delta < 0)
		return (0);
	if (!delta)
	{
		ret[0] = -b / (2 * a);
		return (1);
	}
	ret[0] = (-b + (sqrt(delta))) / (2 * a);
	ret[1] = (-b - (sqrt(delta))) / (2 * a);
	return (2);
}
