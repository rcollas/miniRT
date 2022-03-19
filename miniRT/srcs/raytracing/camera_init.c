#include "miniRT.h"

void	check_limit_angle(double *angle)
{
	if (*angle > 89.0f)
		*angle = 89.0f;
	if (*angle < -89.0f)
		*angle = -89.0f;
}

void	init_euler_angles(t_camera *camera)
{
	camera->pitch_angle = asin(camera->dir->coord[Y]);
	camera->yaw_angle = acos(camera->dir->coord[X] / cos(camera->pitch_angle));
	camera->pitch_angle = convert_rad_to_deg(camera->pitch_angle);
	camera->yaw_angle = convert_rad_to_deg(camera->yaw_angle);
	check_limit_angle(&camera->pitch_angle);
}

void	update_camera_ray(t_ray *cam_ray, t_data *data)
{
	double	ratio;
	double	scale;

	ratio = (double)WIDTH / (double)HEIGHT;
	scale = tan(data->scene->camera->fov * 0.5);
	cam_ray->dir.coord[X] = (2.0 * ((data->pixel_x + 0.5)
				/ (double)WIDTH) - 1.0) * ratio * scale;
	cam_ray->dir.coord[Y] = (1 - 2 * ((data->pixel_y + 0.5)
				/ (double)HEIGHT)) * scale;
	cam_ray->dir.coord[Z] = -1.0;
	cam_ray->dir = mul_dir_and_matrix4(cam_ray->dir, data->cam_to_world_matrix);
	copy_vec3(&cam_ray->origin, *data->scene->camera->origin);
	cam_ray->dir = sub_vec3(cam_ray->dir, cam_ray->origin);
	normalize_vec3(&cam_ray->dir);
	cam_ray->dist = INFINITY;
}

void	init_camera_ray(t_ray *cam_ray, t_data *data)
{
	(void)data;
	cam_ray->origin = create_vec3(0, 0, 0);
	cam_ray->dir.coord[X] = 0;
	cam_ray->dir.coord[Y] = 0;
	cam_ray->dir.coord[Z] = 0;
}
