#include "miniRT.h"

int	exit_hook(t_data *data)
{
	clean_data(data);
	exit(EXIT_SUCCESS);
	return (0);
}

_Bool	handle_arrow_keys(int key, t_camera *camera)
{
	if (key == KEY_UP)
		camera->origin->coord[Y] += 2;
		// *camera->origin = add_vec3(*camera->origin, add_vec3(camera->up, create_vec3(0, 2, 0)));
	else if (key == KEY_DOWN)
		camera->origin->coord[Y] -= 2;
		// *camera->origin = add_vec3(*camera->origin, add_vec3(camera->up, create_vec3(0, -2, 0)));
	else if (key == KEY_RIGHT)
		camera->origin->coord[X] += 2;
		// *camera->origin = add_vec3(*camera->origin, add_vec3(camera->right, create_vec3(2, 0, 0)));
	else if (key == KEY_LEFT)
		camera->origin->coord[X] -= 2;
		// *camera->origin = add_vec3(*camera->origin, add_vec3(camera->right, create_vec3(-2, 0, 0)));
	else if (key == KEY_N)
		camera->origin->coord[Z] -= 2;
		// *camera->origin = add_vec3(*camera->origin, add_vec3(camera->forward, create_vec3(0, 0, -2)));
	else if (key == KEY_M)
		camera->origin->coord[Z] += 2;
		// *camera->origin = add_vec3(*camera->origin, add_vec3(camera->forward, create_vec3(0, 0, 2)));
	// else if (key == KEY_L)
	// 	camera->dir->coord[Y] -= 2;
	// else if (key == KEY_K)
	// 	camera->dir->coord[Y] += 2;
	else
	{
		printf("FAIL\n");
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
	if (handle_arrow_keys(key, data->scene->camera))
		run_raytracing(data->mlx, data->scene, data);
	return (0);
}

void	events_loop(t_data *data)
{
	mlx_hook(data->mlx->window, 17, 0, exit_hook, data);
	mlx_key_hook(data->mlx->window, key_hook, data);
	mlx_loop(data->mlx->ptr);
}
