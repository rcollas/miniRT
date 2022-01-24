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
	mlx->window = mlx_new_window(mlx->ptr, WIDTH, HEIGHT, "Hello world!");
	if (!mlx->window)
		exit_error(mlx);
	mlx->image = mlx_new_image(mlx->ptr, WIDTH, HEIGHT);
	if (!mlx->image)
		exit_error(mlx);
	mlx->addr = mlx_get_data_addr(mlx->image, &mlx->bpp,
			&mlx->size_line, &mlx->endian);
	mlx->bpp /= 8;
	return (mlx);
}
