#include "miniRT.h"

int	exit_hook(t_mlx *mlx)
{
	clean_mlx(mlx);
	exit(EXIT_SUCCESS);
	return (0);
}

int	key_hook(int key, t_mlx *mlx)
{
	if (key == KEY_ESC)
	{
		clean_mlx(mlx);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

void	events_loop(t_mlx *mlx)
{
	mlx_hook(mlx->window, 17, 0, exit_hook, mlx);
	mlx_key_hook(mlx->window, key_hook, mlx);
	mlx_loop(mlx->ptr);
}
