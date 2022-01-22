#ifndef LIB_VECTOR_H
# define LIB_VECTOR_H

typedef struct s_vector3
{
	float	x;
	float	y;
	float	z;
}	t_vector3;

typedef struct s_vector4
{
	float	x;
	float	y;
	float	z;
	float	t;
}	t_vector4;

typedef struct s_matrix4
{
	t_vector3	row_1;
	t_vector3	row_2;
	t_vector3	row_3;
	t_vector3	row_4;
}	t_matrix4;

t_vector3	add_vec3(t_vector3 vector_1, t_vector3 vector_2);
t_vector3	sub_vec3(t_vector3 vector_1, t_vector3 vector_2);
t_vector3	mul_vec3(t_vector3 vector_1, t_vector3 vector_2);
t_vector3	div_vec3(t_vector3 vector_1, t_vector3 vector_2);
t_vector3	add_vec3_and_const(t_vector3 vector, float k);
t_vector3	sub_vec3_and_const(t_vector3 vector, float k);
t_vector3	mul_vec3_and_const(t_vector3 vector, float k);
t_vector3	add_vec3_and_const(t_vector3 vector, float k);

float		dot_product_vec3(t_vector3 vector_1, t_vector3 vector_2);
t_vector3	cross_product_vec3(t_vector3 vector_1, t_vector3 vector_2);
float		get_norm_vec3(t_vector3 vector);
t_vector4	convert_vec3_to_vec4(t_vector3 vector);

#endif