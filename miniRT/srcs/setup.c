#include "miniRT.h"

t_mlx	*setup_mlx(void)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)ft_calloc(1, sizeof(t_mlx));
	if (!mlx)
		exit_error(mlx);
	mlx->ptr = mlx_init();
	if (!mlx->ptr)
		exit_error(mlx);
	mlx->window = mlx_new_window(mlx->ptr, 1920, 1080, "Hello world!");
	if (!mlx->window)
		exit_error(mlx);
	mlx->bpp /= 8;
	return (mlx);
}
