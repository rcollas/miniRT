#include "miniRT.h"

void	clean_mlx(t_mlx *mlx)
{
	if (!mlx)
		return ;
	if (mlx->image)
	{
		mlx_destroy_image(mlx->ptr, mlx->image->img_ptr);
		ft_free(mlx->image);
	}
	if (mlx->window)
	{
		mlx_destroy_window(mlx->ptr, mlx->window);
		mlx->window = NULL;
	}
	if (IS_LINUX)
		mlx_destroy_display(mlx->ptr);
	ft_free(mlx->ptr);
	mlx->ptr = NULL;
	ft_free(mlx);
	mlx = NULL;
}

void	clean_data(t_data *data)
{
	free_list(data->obj);
	clean_mlx(data->mlx);
}
