#include "miniRT.h"

void	clean_mlx(t_mlx *mlx)
{
	if (!mlx)
		return ;
	if (mlx->image)
	{
		mlx_destroy_image(mlx->ptr, mlx->image);
		mlx->image = NULL;
	}
	if (mlx->window)
	{
		mlx_destroy_window(mlx->ptr, mlx->window);
		mlx->window = NULL;
	}
	mlx_destroy_display(mlx->ptr);
	free(mlx->ptr);
	mlx->ptr = NULL;
	free(mlx);
	mlx = NULL;
}

void	clean_data(t_data *data)
{
	free_list(data->obj);
	clean_mlx(data->mlx);
}
