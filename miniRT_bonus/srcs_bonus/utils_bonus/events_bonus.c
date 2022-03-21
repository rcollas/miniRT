#include "miniRT_bonus.h"

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
		camera->yaw_angle += 5.0;
	else if (key == KEY_LEFT)
		camera->yaw_angle -= 5.0;
	else if (key == KEY_DOWN)
		camera->pitch_angle += 5.0;
	else if (key == KEY_UP)
		camera->pitch_angle -= 5.0;
	else
		return (0);
	return (1);
}

void	run_pathtracing(t_data *data)
{
	data->path_tracing = PATH_TRACING;
	data->multithreading = MULTITHREADING;
	ft_putchar_fd('\n', 1);
	if (data->mlx->image)
	{
		mlx_destroy_image(data->mlx->ptr, data->mlx->image->img_ptr);
		ft_free(data->mlx->image);
	}
	run_minirt(data);
}

int	key_hook(int key, t_data *data)
{
	if (key == KEY_ESC)
		return (exit_hook(data));
	if (move_camera(key, data->scene->camera)
		|| tilt_camera(key, data->scene->camera))
	{
		data->path_tracing = NO_PATH_TRACING;
		if (data->mlx->image)
		{
			mlx_destroy_image(data->mlx->ptr, data->mlx->image->img_ptr);
			ft_free(data->mlx->image);
		}
		run_minirt(data);
	}
	if (key == KEY_P)
	{
		run_pathtracing(data);
	}
	return (0);
}

void	events_loop(t_data *data)
{
	mlx_hook(data->mlx->window, 17, 0, exit_hook, data);
	mlx_key_hook(data->mlx->window, key_hook, data);
	mlx_loop(data->mlx->ptr);
}
