#ifndef LIB_VECTOR_H
# define LIB_VECTOR_H

# include "miniRT.h"

typedef struct s_vec4
{
	double	x;
	double	y;
	double	z;
	double	t;
}	t_vec4;

typedef struct s_matrix4
{
	t_vec4	row_1;
	t_vec4	row_2;
	t_vec4	row_3;
	t_vec4	row_4;
}	t_matrix4;

t_vec3		create_vec3(double x, double y, double z);
t_vec4		create_vec4(double x, double y, double z, double t);
t_vec3		add_vec3(t_vec3 vector_1, t_vec3 vector_2);
t_vec3		sub_vec3(t_vec3 vector_1, t_vec3 vector_2);
t_vec3		add_vec3_and_const(t_vec3 vector, double k);
t_vec3		sub_vec3_and_const(t_vec3 vector, double k);
t_vec3		mul_vec3_and_const(t_vec3 vector, double k);
t_vec3		div_vec3_and_const(t_vec3 vector, double k);

double		dot_product_vec3(t_vec3 vector_1, t_vec3 vector_2);
t_vec3		cross_product_vec3(t_vec3 vector_1, t_vec3 vector_2);
double		get_norm_vec3(t_vec3 vector);
double		get_norm2_vec3(t_vec3 vector);
void		normalize_vec3(t_vec3 *vector);
t_vec3		get_normalized_vec3(t_vec3 vector);
t_vec4		conver_vec3_to_vec4(t_vec3 vector);
void		copy_vec3(t_vec3 *dest, t_vec3 *src);

#endif