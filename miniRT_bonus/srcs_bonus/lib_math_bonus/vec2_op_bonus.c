#include "miniRT_bonus.h"

double	dot_vec2(t_vec2 vector_1, t_vec2 vector_2)
{
	return (vector_1.coord[X] * vector_2.coord[X]
		+ vector_1.coord[Y] * vector_2.coord[Y]);
}

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

t_vec2	create_vec2(double x, double y)
{
	t_vec2	new_vector;

	new_vector.coord[X] = x;
	new_vector.coord[Y] = y;
	return (new_vector);
}
