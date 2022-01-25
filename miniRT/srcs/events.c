#include "miniRT.h"

int	exit_hook(t_data *data)
{
	clean_data(data);
	exit(EXIT_SUCCESS);
	return (0);
}

int	key_hook(int key, t_data *data)
{
	if (key == KEY_ESC)
	{
		clean_data(data);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

void	events_loop(t_data *data)
{
	mlx_hook(data->mlx->window, 17, 0, exit_hook, data);
	mlx_key_hook(data->mlx->window, key_hook, data);
	mlx_loop(data->mlx->ptr);
}
