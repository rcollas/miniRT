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
	free_tab((void **)&data->scene->diffuse_light, data->scene->light_nb);
	clean_mlx(data->mlx);
}

void	exit_error(int errnum, char *error_msg, t_data *data)
{
	if (error_msg)
	{
		ft_putstr_fd("Error: ", 2);
		ft_putstr_fd(error_msg, 2);
		ft_putstr_fd("\n", 2);
	}
	clean_data(data);
	exit(errnum);
}

void	clean_parsing_var(t_parsing *parsing_var)
{
	free_list(parsing_var->objs);
	free_str_tab(parsing_var->input_list);
	free_str_tab(parsing_var->obj_info);
	free_tab((void **)&parsing_var->scene->diffuse_light, parsing_var->light_nb);
	//clean_mlx(parsing_var->mlx);
}

void	exit_error_parsing(int errnum, char *error_msg, t_parsing *parsing_var)
{
	if (error_msg)
	{
		ft_putstr_fd("Error: ", 2);
		ft_putstr_fd(error_msg, 2);
		ft_putstr_fd("\n", 2);
	}
	clean_parsing_var(parsing_var);
	exit(errnum);
}
