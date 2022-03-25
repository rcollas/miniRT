/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:42:56 by efrancon          #+#    #+#             */
/*   Updated: 2022/03/25 11:56:41 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

void	init_mlx_all(t_mlx *mlx)
{
	mlx->ptr = NULL;
	mlx->image = NULL;
	mlx->window = NULL;
	mlx->ptr = mlx_init();
}

t_mlx	*setup_mlx(t_parsing *parsing_var)
{
	t_mlx	*mlx;

	mlx = NULL;
	mlx = (t_mlx *)ft_calloc(1, sizeof(t_mlx));
	if (!mlx)
		exit_error_parsing(MALLOC_ERROR, "malloc() failed", parsing_var);
	ft_memset(mlx, 0, sizeof(t_mlx *));
	init_mlx_all(mlx);
	if (!mlx->ptr)
	{
		ft_free(mlx);
		exit_error_parsing(MLX_ERROR, "mlx_init() failed", parsing_var);
	}
	mlx->window = mlx_new_window(mlx->ptr, WIDTH, HEIGHT, "miniRT");
	if (!mlx->window)
	{
		if (IS_LINUX)
			mlx_destroy_display(mlx->ptr);
		ft_free(mlx->ptr);
		ft_free(mlx);
		exit_error_parsing(MLX_ERROR, "mlx_new_window() failed", parsing_var);
	}
	return (mlx);
}

void	init_image_all(t_image *image)
{
	ft_memset(image, 0, sizeof(t_image *));
	image->img_ptr = NULL;
	image->addr = NULL;
	image->bpp = 0;
	image->line_len = 0;
	image->endian = 0;
	image->width = 0;
	image->height = 0;
}

void	init_image(t_mlx *mlx, t_data *data)
{
	t_image	*image;

	image = NULL;
	image = (t_image *)ft_calloc(1, sizeof(t_image));
	if (!image)
		exit_error(MALLOC_ERROR, "malloc() failed", data);
	init_image_all(image);
	image->img_ptr = mlx_new_image(mlx->ptr, WIDTH, HEIGHT);
	if (!image->img_ptr)
	{
		ft_free(image);
		exit_error(MLX_ERROR, "mlx_new_image() failed", data);
	}
	image->addr = mlx_get_data_addr(
			image->img_ptr, &image->bpp, &image->line_len, &image->endian);
	if (!image->addr)
	{
		mlx_destroy_image(mlx->ptr, image->img_ptr);
		ft_free(image);
		exit_error(MLX_ERROR, "mlx_get_data_addr() failed", data);
	}
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
	data->mlx = parsing_var->mlx;
	data->scene->camera->right = create_vec3(0, 0, 0);
	data->scene->camera->up = create_vec3(0, 0, 0);
	data->scene->camera->forward = create_vec3(0, 0, 0);
}
