#include "miniRT.h"

void	compute_the_axis(t_camera camera, t_vec3 *x_axis, t_vec3 *y_axis, t_vec3 *z_axis)
{
	t_vec3	tmp;

	*z_axis = get_normalized_vec3(inverse_vec3(*camera.dir));
	tmp = create_vec3(0, 1, 0); // Special case to handle : when z_axis ( = cam->dir ) == (0, -1, 0) ou (0, 1, 0)
	// if (z_axis.y == -1 || z_axis.y == 1)
	*x_axis = cross_vec3(get_normalized_vec3(tmp), *z_axis);
	*y_axis = cross_vec3(*z_axis, *x_axis);
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
	matrix.row_4 = create_vec4(0, 0, 0, 1);
	// matrix.row_4 = create_vec4(camera->origin->x, camera->origin->y, camera->origin->z, 1);
	// printf("row_1[x] = %f    row_1[y] = %f    row_1[z] = %f    row_1[t] = %f\n", matrix.row_1.x, matrix.row_1.y, matrix.row_1.z, matrix.row_1.t);
	// printf("row_2[x] = %f    row_2[y] = %f    row_2[z] = %f    row_2[t] = %f\n", matrix.row_2.x, matrix.row_2.y, matrix.row_2.z, matrix.row_2.t);
	// printf("row_3[x] = %f    row_3[y] = %f    row_3[z] = %f    row_3[t] = %f\n", matrix.row_3.x, matrix.row_3.y, matrix.row_3.z, matrix.row_3.t);
	// printf("row_4[x] = %f    row_4[y] = %f    row_4[z] = %f    row_4[t] = %f\n", matrix.row_4.x, matrix.row_4.y, matrix.row_4.z, matrix.row_4.t);
	return (matrix);
}

void	init_camera_ray(t_ray *cam_ray, t_scene *scene)
{
	(void)scene;
	// copy_vec3(&cam_ray->origin, scene->camera->origin);
	cam_ray->origin = create_vec3(0, 0, 0);
	cam_ray->dir.x = 0;
	cam_ray->dir.y = 0;
	cam_ray->dir.z = 0;
	// cam_ray->dir.z = -1 * (WIDTH / (2 * tan(scene->camera->fov / 2)));
}

// void	update_camera_ray(t_ray *cam_ray, t_data *data)
// {
// 	cam_ray->dir.y = data->pixel_y - HEIGHT / 2;
// 	cam_ray->dir.x = data->pixel_x - WIDTH / 2;
// 	normalize_vec3(&cam_ray->dir);
// 	cam_ray->dir = mul_vec3_and_matrix4(cam_ray->dir, data->cam_to_world_matrix);
// 	// printf("x = %f | y = %f | z = %f\n", cam_ray->dir.x, cam_ray->dir.y, cam_ray->dir.z);
// 	normalize_vec3(&cam_ray->dir);
// }

void	update_camera_ray(t_ray *cam_ray, t_data *data)
{
	double	ratio;
	double	scale;

	ratio = (double)WIDTH / (double)HEIGHT;
	scale = tan(data->scene->camera->fov * 0.5);
	cam_ray->dir.x = (2 * (data->pixel_x + 0.5) / (double)WIDTH - 1) * ratio * scale; 
	cam_ray->dir.y = (1 - 2 * (data->pixel_y + 0.5) / (double)HEIGHT) * scale; 
	cam_ray->dir.z = -1;
	cam_ray->dir = mul_vec3_and_matrix4(cam_ray->dir, data->cam_to_world_matrix);
	get_normalized_vec3(cam_ray->dir);
}
