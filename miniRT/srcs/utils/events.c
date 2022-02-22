#include "miniRT.h"

int	exit_hook(t_data *data)
{
	clean_data(data);
	printf("\n");
	exit(EXIT_SUCCESS);
	return (0);
}

_Bool	move_camera(int key, t_camera *camera)
{
	t_vec3	*origin;

	origin = camera->origin;
	if (key == KEY_D)
		*origin = add_vec3(*origin, mul_vec3_and_const(camera->right, 2));
	else if (key == KEY_A)
		*origin = add_vec3(*origin, mul_vec3_and_const(camera->right, -2));
	else if (key == KEY_SPACE)
		*origin = add_vec3(*origin, mul_vec3_and_const(camera->up, 2));
	else if (key == KEY_MAJ)
		*origin = add_vec3(*origin, mul_vec3_and_const(camera->up, -2));
	else if (key == KEY_W)
		*origin = add_vec3(*origin, mul_vec3_and_const(camera->forward, -4));
	else if (key == KEY_S)
		*origin = add_vec3(*origin, mul_vec3_and_const(camera->forward, 4));
	else
		return (0);
	return (1);
}

_Bool	tilt_camera(int key, t_camera *camera)
{
	if (key == KEY_RIGHT)
		camera->yaw_angle += 6.0;
	else if (key == KEY_LEFT)
		camera->yaw_angle -= 6.0;
	else if (key == KEY_DOWN)
		camera->pitch_angle += 6.0;
	else if (key == KEY_UP)
		camera->pitch_angle -= 6.0;
	else
		return (0);
	return (1);
}

int	key_hook(int key, t_data *data)
{
	if (key == KEY_ESC)
		return (exit_hook(data));
	if (move_camera(key, data->scene->camera)
		|| tilt_camera(key, data->scene->camera))
		run_raytracing(data->mlx, data->scene, data, NO_PATH_TRACING);
	if (key == KEY_P)
	{
		ft_putstr_fd("\n\033[38;5;123mRendering with path_tracing...\n\n\033[0m", 1);
		run_raytracing(data->mlx, data->scene, data, PATH_TRACING);
	}
	return (0);
}

void	events_loop(t_data *data)
{
	mlx_hook(data->mlx->window, 17, 0, exit_hook, data);
	mlx_key_hook(data->mlx->window, key_hook, data);
	mlx_loop(data->mlx->ptr);
}
