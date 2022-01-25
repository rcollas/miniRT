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
	return (mlx);
}

void	init_image(t_mlx *mlx)
{
	t_image *image;

	image = (t_image *)malloc(sizeof(t_image));
	image->img_ptr = mlx_new_image(mlx->ptr, WIDTH, HEIGHT);
	if (!image->img_ptr)
		exit_error(mlx);
	image->addr = mlx_get_data_addr(image->img_ptr, &image->bpp, &image->line_len, &image->endian);
	mlx->image = image;
}
