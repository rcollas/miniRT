#ifndef LIB_MATH_H
# define LIB_MATH_H

typedef struct s_vec3
{
	double	coord[3];
}	t_vec3;

typedef struct s_vec4
{
	double	coord[4];
}	t_vec4;

typedef struct s_matrix4
{
	t_vec4	row_1;
	t_vec4	row_2;
	t_vec4	row_3;
	t_vec4	row_4;
}	t_matrix4;

/****************************** VEC3 INIT ************************************/

t_vec3			create_vec3(double x, double y, double z);
t_vec3			convert_vec4_to_vec3(t_vec4 vector);
void			copy_vec3(t_vec3 *dest, t_vec3 src);

/****************************** VEC4 INIT ************************************/

t_vec4			create_vec4(double x, double y, double z, double t);
t_vec4			convert_vec3_to_vec4(t_vec3 vector);

/******************************* VEC3 OP *************************************/

t_vec3			add_vec3(t_vec3 vector_1, t_vec3 vector_2);
t_vec3			sub_vec3(t_vec3 vector_1, t_vec3 vector_2);
t_vec3			mul_vec3(t_vec3 vector_1, t_vec3 vector_2);
t_vec3			inverse_vec3(t_vec3 vector);
double			dot_vec3(t_vec3 vector_1, t_vec3 vector_2);
t_vec3			cross_vec3(t_vec3 vector_1, t_vec3 vector_2);

/************************** VEC3 AND CONST OP ********************************/

t_vec3			add_vec3_and_const(t_vec3 vector, double k);
t_vec3			sub_vec3_and_const(t_vec3 vector, double k);
t_vec3			mul_vec3_and_const(t_vec3 vector, double k);
t_vec3			div_vec3_and_const(t_vec3 vector, double k);

/****************************** VEC3 NORM ************************************/

double			get_norm_vec3(t_vec3 vector);
double			get_norm2_vec3(t_vec3 vector);
void			normalize_vec3(t_vec3 *vector);
t_vec3			get_normalized_vec3(t_vec3 vector);

/********************************* MATRIX ************************************/

t_vec3			mul_vec3_and_matrix4(t_vec3 vector, t_matrix4 matrix);
t_vec3			mul_dir_and_matrix4(t_vec3 vector, t_matrix4 matrix);

/********************************** TRIGO ************************************/

double			convert_deg_to_rad(double angle);
double			convert_rad_to_deg(double angle);

/********************************** FRAND ************************************/

float			frand(void);
unsigned int	ft_rand(void);

/********************************* ALGEBRA ************************************/

_Bool			solve_quadratic_equation(
					double *coeff, double *roots, double *closest_hit);

#endif
