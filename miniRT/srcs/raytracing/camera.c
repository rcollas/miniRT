#include "miniRT.h"

_Bool	cam_is_vertical_looking(t_vec3 z_axis)
{
	return (z_axis.coord[X] == 0 && (z_axis.coord[Y] == -1 || z_axis.coord[Y] == 1) && z_axis.coord[Z] == 0);
}

void	compute_the_axis(t_camera *camera)
{
	t_vec3	tmp;

	camera->forward = get_normalized_vec3(inverse_vec3(*camera->dir));
	if (cam_is_vertical_looking(camera->forward)) // Special case to handle : when z_axis ( = cam->dir ) == (0, -1, 0) ou (0, 1, 0)
		tmp = create_vec3(1, 0, 0);
	else
		tmp = create_vec3(0, 1, 0);
	camera->right = cross_vec3(get_normalized_vec3(tmp), camera->forward);
	camera->up = cross_vec3(camera->forward, camera->right);
}

void	print_matrix(t_matrix4 matrix)
{
	printf("row_1[x] = %f    row_1[y] = %f    row_1[z] = %f\n", matrix.row_1.coord[X], matrix.row_1.coord[Y], matrix.row_1.coord[Z]);
	printf("row_2[x] = %f    row_2[y] = %f    row_2[z] = %f\n", matrix.row_2.coord[X], matrix.row_2.coord[Y], matrix.row_2.coord[Z]);
	printf("row_3[x] = %f    row_3[y] = %f    row_3[z] = %f\n", matrix.row_3.coord[X], matrix.row_3.coord[Y], matrix.row_3.coord[Z]);
	printf("row_4[x] = %f    row_4[y] = %f    row_4[z] = %f\n", matrix.row_4.coord[X], matrix.row_4.coord[Y], matrix.row_4.coord[Z]);
}

t_matrix4	built_cam_to_word_matrix(t_camera *camera)
{
	t_matrix4	matrix;

	compute_the_axis(camera);
	matrix.row_1 = create_vec4(camera->right.coord[X], camera->right.coord[Y], camera->right.coord[Z], 0);
	matrix.row_2 = create_vec4(camera->up.coord[X], camera->up.coord[Y], camera->up.coord[Z], 0);
	matrix.row_3 = create_vec4(camera->forward.coord[X], camera->forward.coord[Y], camera->forward.coord[Z], 0);
	matrix.row_4 = create_vec4(camera->origin->coord[X], camera->origin->coord[Y], camera->origin->coord[Z], 1);
	return (matrix);
}

void	init_camera_ray(t_ray *cam_ray, t_data *data)
{
	(void)data;
	cam_ray->origin = create_vec3(0, 0, 0);
	cam_ray->dir.coord[X] = 0;
	cam_ray->dir.coord[Y] = 0;
	cam_ray->dir.coord[Z] = 0;
}

// void	update_camera_ray(t_ray *cam_ray, t_data *data)
// {
// 	cam_ray->dir.y = data->pixel_y - HEIGHT / 2;
// 	cam_ray->dir.x = data->pixel_x - WIDTH / 2;
// 	normalize_vec3(&cam_ray->dir);
// 	cam_ray->dir = mul_vec3_and_matrix4(cam_ray->dir, data->cam_to_world_matrix);
// 	normalize_vec3(&cam_ray->dir);
// 	// printf("x = %f | y = %f | z = %f\n", cam_ray->dir.x, cam_ray->dir.y, cam_ray->dir.z);
// }

void	update_camera_ray(t_ray *cam_ray, t_data *data)
{
	double	ratio;
	double	scale;

	ratio = (double)WIDTH / (double)HEIGHT;
	scale = tan(data->scene->camera->fov * 0.5);
	cam_ray->dir.coord[X] = (2.0 * ((data->pixel_x + 0.5) / (double)WIDTH) - 1.0) * ratio * scale; 
	cam_ray->dir.coord[Y] = (1 - 2 * ((data->pixel_y + 0.5) / (double)HEIGHT)) * scale; 
	cam_ray->dir.coord[Z] = -1.0;
	// printf("x = %f | y = %f | z = %f\n", cam_ray->dir.x, cam_ray->dir.y, cam_ray->dir.z);
	cam_ray->dir = mul_dir_and_matrix4(cam_ray->dir, data->cam_to_world_matrix);
	copy_vec3(&cam_ray->origin, *data->scene->camera->origin);
	cam_ray->dir = sub_vec3(cam_ray->dir, cam_ray->origin);
	get_normalized_vec3(cam_ray->dir);
}

