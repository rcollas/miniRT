#include "miniRT.h"

t_mlx	*setup_mlx(t_parsing *parsing_var)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)ft_calloc(1, sizeof(t_mlx));
	if (!mlx)
		exit_error_parsing(MALLOC_ERROR, "malloc() failed", parsing_var);
	mlx->ptr = mlx_init();
	if (!mlx->ptr)
		exit_error_parsing(MLX_ERROR, "mlx_init() failed", parsing_var);
	mlx->window = mlx_new_window(mlx->ptr, WIDTH, HEIGHT, "miniRT");
	if (!mlx->window)
		exit_error_parsing(MLX_ERROR, "mlx_new_window() failed", parsing_var);
	return (mlx);
}

void	init_image(t_mlx *mlx, t_data *data)
{
	t_image	*image;

	image = (t_image *)ft_calloc(1, sizeof(t_image));
	if (!image)
		exit_error(MALLOC_ERROR, "malloc() failed", data);
	image->img_ptr = mlx_new_image(mlx->ptr, WIDTH, HEIGHT);
	if (!image->img_ptr)
		exit_error(MLX_ERROR, "mlx_new_image() failed", data);
	image->addr = mlx_get_data_addr(
			image->img_ptr, &image->bpp, &image->line_len, &image->endian);
	if (!image->addr)
		exit_error(MLX_ERROR, "mlx_get_data_addr() failed", data);
	mlx->image = image;
}

void	init_data(t_parsing *parsing_var, t_data *data)
{
	data->lighting = CLASSIC_LIGHTING;
	data->path_tracing = NO_PATH_TRACING;
	data->multithreading = NO_MULTITHREADING;
	if (BONUS)
	{
		data->lighting = PHONG_LIGHTING;
		data->path_tracing = NO_PATH_TRACING;
		data->multithreading = MULTITHREADING;
	}
	data->obj = parsing_var->objs;
	data->scene = parsing_var->scene;
	data->obj_nb = parsing_var->obj_nb;
	data->mlx = setup_mlx(parsing_var);
}
