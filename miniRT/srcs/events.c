#include "miniRT.h"

int	exit_hook(t_data *data)
{
	clean_data(data);
	exit(EXIT_SUCCESS);
	return (0);
}

_Bool	handle_arrow_keys(int key, t_data *data, t_camera *camera)
{
	// printf("keycode = %d\n", key);
	if (key == KEY_UP)
	{
		*camera->origin = add_vec3(*camera->origin, create_vec3(0, 2, 0));
		// *camera->origin = add_vec3(*camera->origin, add_vec3(camera->up, create_vec3(0, 2, 0)));
		// printf("up : x = %f | y = %f | z = %f\n", camera->up.coord[X], camera->up.coord[Y], camera->up.coord[Z]);
		// printf("origin : x = %f | y = %f | z = %f\n", camera->origin->coord[X], camera->origin->coord[Y], camera->origin->coord[Z]);
	}
	else if (key == KEY_DOWN)
	{
		*camera->origin = add_vec3(*camera->origin, create_vec3(0, -2, 0));
		// *camera->origin = add_vec3(*camera->origin, add_vec3(camera->up, create_vec3(0, -2, 0)));
		// printf("up : x = %f | y = %f | z = %f\n", camera->up.coord[X], camera->up.coord[Y], camera->up.coord[Z]);
		// printf("origin : x = %f | y = %f | z = %f\n", camera->origin->coord[X], camera->origin->coord[Y], camera->origin->coord[Z]);
	}
	else if (key == KEY_RIGHT)
	{
		*camera->origin = add_vec3(*camera->origin, create_vec3(2, 0, 0));
		// *camera->origin = add_vec3(*camera->origin, add_vec3(camera->right, create_vec3(2, 0, 0)));
	}
	else if (key == KEY_LEFT)
	{
		// printf("right : x = %f | y = %f | z = %f\n", camera->right.coord[X], camera->right.coord[Y], camera->right.coord[Z]);
		*camera->origin = add_vec3(*camera->origin, create_vec3(-2, 0, 0));
		// *camera->origin = add_vec3(*camera->origin, add_vec3(camera->right, create_vec3(-2, 0, 0)));
	}
	else if (key == KEY_SPACE)
		*camera->origin = add_vec3(*camera->origin, create_vec3(0, 0, -2));
		// *camera->origin = add_vec3(*camera->origin, add_vec3(camera->forward, create_vec3(0, 0, -2)));
	else if (key == KEY_MAJ)
		*camera->origin = add_vec3(*camera->origin, create_vec3(0, 0, 2));
		// *camera->origin = add_vec3(*camera->origin, add_vec3(camera->forward, create_vec3(0, 0, 2)));
	else if (key == KEY_J)
		camera->yaw_angle += 5.0;
	else if (key == KEY_H)
		camera->yaw_angle -= 5.0;
	else if (key == KEY_L)
		camera->pitch_angle += 5.0;
	else if (key == KEY_K)
		camera->pitch_angle -= 5.0;
	else 
	{
		if (key == KEY_P)
		{
			ft_putstr_fd("\033[38;5;123mRendering with path_tracing...\n\033[0m", 1);
			run_raytracing(data->mlx, data->scene, data, PATH_TRACING);
		}
		return (0);
	}
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
