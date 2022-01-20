#include "miniRT.h"

int	exit_hook(void)
{
	exit(EXIT_SUCCESS);
	return (0);
}

int	key_hook(int key)
{
	if (key == KEY_ESC)
		exit(EXIT_SUCCESS);
	return (0);
}

void	events_loop(t_mlx *mlx)
{
	mlx_hook(mlx->window, 17, 0, exit_hook, NULL);
	mlx_key_hook(mlx->window, key_hook, NULL);
	mlx_loop(mlx->ptr);
}
