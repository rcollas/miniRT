#include "miniRT.h"

void	compute_the_axis(t_camera camera, t_vec3 *x_axis, t_vec3 *y_axis, t_vec3 *z_axis)
{
	t_vec3	tmp;

	*z_axis = get_normalized_vec3(*camera.dir);
	tmp = create_vec3(0, 1, 0); // Special case to handle : when z_axis ( = cam->dir ) == (0, -1, 0) ou (0, 1, 0)
	// if (z_axis.y == -1 || z_axis.y == 1)
	*x_axis = cross_product_vec3(get_normalized_vec3(tmp), *z_axis);
	*y_axis = cross_product_vec3(*z_axis, *x_axis);
}

t_matrix4	built_cam_to_word_matrix(t_camera *camera)
{
	t_vec3		x_axis;
	t_vec3		y_axis;
	t_vec3		z_axis;
	t_matrix4	matrix;

	compute_the_axis(*camera, &x_axis, &y_axis, &z_axis);
	matrix.row_1 = create_vec4(x_axis.x, x_axis.y, x_axis.z, 0);
	matrix.row_2 = create_vec4(y_axis.x, y_axis.y, y_axis.z, 0);
	matrix.row_3 = create_vec4(z_axis.x, z_axis.y, z_axis.z, 0);
	matrix.row_4 = create_vec4(camera->origin->x, camera->origin->y, camera->origin->z, 1);
	return (matrix);
}
