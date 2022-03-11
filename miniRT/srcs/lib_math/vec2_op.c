#include "miniRT.h"

double	get_norm_vec2(t_vec2 vector)
{
	double	norm;

	norm = vector.coord[X] * vector.coord[X];
	norm += vector.coord[Y] * vector.coord[Y];
	norm = sqrt(norm);
	return (norm);
}

void	normalize_vec2(t_vec2 *vector)
{
	double	norm;

	norm = get_norm_vec2(*vector);
	vector->coord[X] /= norm;
	vector->coord[V] /= norm;
}
