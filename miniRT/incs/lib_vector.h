#ifndef LIB_VECTOR_H
# define LIB_VECTOR_H

# include "miniRT.h"

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

struct s_vec3	add_vec3(struct s_vec3 vector_1, struct s_vec3 vector_2);
struct s_vec3	sub_vec3(struct s_vec3 vector_1, struct s_vec3 vector_2);
struct s_vec3	add_vec3_and_const(struct s_vec3 vector, float k);
struct s_vec3	sub_vec3_and_const(struct s_vec3 vector, float k);
struct s_vec3	mul_vec3_and_const(struct s_vec3 vector, float k);
struct s_vec3	add_vec3_and_const(struct s_vec3 vector, float k);

float		dot_product_vec3(struct s_vec3 vector_1, struct s_vec3 vector_2);
struct s_vec3	cross_product_vec3(struct s_vec3 vector_1, struct s_vec3 vector_2);
float		get_norm_vec3(struct s_vec3 vector);
void		normalize_vec3(struct s_vec3 *vector);
t_vec4	conver_vec3_to_vec4(struct s_vec3 vector);

#endif