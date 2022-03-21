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

void	clean_parsing_var(t_parsing *parsing_var)
{
	free_list_error(parsing_var->objs);
	free_str_tab(parsing_var->input_list);
	free_str_tab(parsing_var->obj_info);
	clean_mlx(parsing_var->mlx);
}
