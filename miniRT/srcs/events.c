#include "miniRT.h"

int	exit_hook(t_data *data)
{
	clean_data(data);
	exit(EXIT_SUCCESS);
	return (0);
}

_Bool	handle_path_tracing(int key, t_data *data)
{
	if (key == KEY_P)
	{
		ft_putstr_fd("\n\033[38;5;123mRendering with path_tracing...\n\n\033[0m", 1);
		run_raytracing(data->mlx, data->scene, data, PATH_TRACING);
	}
	return (0);
}

_Bool	handle_arrow_keys(int key, t_data *data, t_camera *camera)
{
	// printf("keycode = %d\n", key);
	if (key == KEY_SPACE)
		*camera->origin = add_vec3(*camera->origin, mul_vec3_and_const(camera->up, 2));
	else if (key == KEY_MAJ)
		*camera->origin = add_vec3(*camera->origin, mul_vec3_and_const(camera->up, -2));
	else if (key == KEY_D)
		*camera->origin = add_vec3(*camera->origin, mul_vec3_and_const(camera->right, 2));
	else if (key == KEY_A)
		*camera->origin = add_vec3(*camera->origin, mul_vec3_and_const(camera->right, -2));
	else if (key == KEY_W)
		*camera->origin = add_vec3(*camera->origin, mul_vec3_and_const(camera->forward, -4));
	else if (key == KEY_S)
		*camera->origin = add_vec3(*camera->origin, mul_vec3_and_const(camera->forward, 4));
	else if (key == KEY_RIGHT)
		camera->yaw_angle += 6.0;
	else if (key == KEY_LEFT)
		camera->yaw_angle -= 6.0;
	else if (key == KEY_DOWN)
		camera->pitch_angle += 6.0;
	else if (key == KEY_UP)
		camera->pitch_angle -= 6.0;
	else
		return (handle_path_tracing(key, data));
	return (1);
}

int	key_hook(int key, t_data *data)
{
	if (key == KEY_ESC)
	{
		clean_data(data);
		exit(EXIT_SUCCESS);
	}
	if (handle_arrow_keys(key, data, data->scene->camera))
		run_raytracing(data->mlx, data->scene, data, NO_PATH_TRACING);
	return (0);
}

void	events_loop(t_data *data)
{
	mlx_hook(data->mlx->window, 17, 0, exit_hook, data);
	mlx_key_hook(data->mlx->window, key_hook, data);
	mlx_loop(data->mlx->ptr);
}
