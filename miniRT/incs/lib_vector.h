#ifndef LIB_VECTOR_H
# define LIB_VECTOR_H

typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
}	t_vec3;

typedef struct s_vec4
{
	float	x;
	float	y;
	float	z;
	float	t;
}	t_vec4;

typedef struct s_matrix4
{
	t_vec4	row_1;
	t_vec4	row_2;
	t_vec4	row_3;
	t_vec4	row_4;
}	t_matrix4;

t_vec3	add_vec3(t_vec3 vector_1, t_vec3 vector_2);
t_vec3	sub_vec3(t_vec3 vector_1, t_vec3 vector_2);
t_vec3	add_vec3_and_const(t_vec3 vector, float k);
t_vec3	sub_vec3_and_const(t_vec3 vector, float k);
t_vec3	mul_vec3_and_const(t_vec3 vector, float k);
t_vec3	add_vec3_and_const(t_vec3 vector, float k);

float	dot_product_vec3(t_vec3 vector_1, t_vec3 vector_2);
t_vec3	cross_product_vec3(t_vec3 vector_1, t_vec3 vector_2);
float	get_norm_vec3(t_vec3 vector);
void	normalize_vec3(t_vec3 *vector);
t_vec4	convert_vec3_to_vec4(t_vec3 vector);
t_vec3	convert_vec4_to_vec3(t_vec4 vector);

#endif