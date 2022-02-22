#include "miniRT.h"

void	compute_cam_dir(t_camera *camera)
{
	float	yaw;
	float	pitch;

	check_limit_angle(&camera->pitch_angle);
	yaw = convert_deg_to_rad(camera->yaw_angle);
	pitch = convert_deg_to_rad(camera->pitch_angle);
	camera->dir->coord[X] = cos(yaw) * cos(pitch);
	camera->dir->coord[Y] = sin(pitch);
	camera->dir->coord[Z] = sin(yaw) * cos(pitch);
}

_Bool	cam_is_vertical_looking(t_vec3 z_axis)
{
	return (z_axis.coord[X] == 0 && (z_axis.coord[Y] == -1
			|| z_axis.coord[Y] == 1) && z_axis.coord[Z] == 0);
}

void	compute_cam_axis(t_camera *camera)
{
	t_vec3	tmp;

	compute_cam_dir(camera);
	// camera->forward = get_normalized_vec3(inverse_vec3(*camera->dir));
	camera->forward = get_normalized_vec3(*camera->dir);
	if (cam_is_vertical_looking(camera->forward))
		tmp = create_vec3(1, 0, 0);
	else
		tmp = create_vec3(0, 1, 0);
	camera->right = cross_vec3(get_normalized_vec3(tmp), camera->forward);
	camera->up = cross_vec3(camera->forward, camera->right);
}

t_matrix4	built_cam_to_world_matrix(t_camera *camera)
{
	t_matrix4	matrix;

	compute_cam_axis(camera);
	matrix.row_1 = create_vec4(camera->right.coord[X],
			camera->right.coord[Y], camera->right.coord[Z], 0);
	matrix.row_2 = create_vec4(camera->up.coord[X],
			camera->up.coord[Y], camera->up.coord[Z], 0);
	matrix.row_3 = create_vec4(camera->forward.coord[X],
			camera->forward.coord[Y], camera->forward.coord[Z], 0);
	matrix.row_4 = create_vec4(camera->origin->coord[X],
			camera->origin->coord[Y], camera->origin->coord[Z], 1);
	return (matrix);
}
