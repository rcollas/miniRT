/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:41:40 by efrancon          #+#    #+#             */
/*   Updated: 2022/03/25 14:03:20 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

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

void	destroy_texture(t_obj *obj, int obj_nb, t_mlx *mlx)
{
	int	i;

	i = -1;
	if (obj)
	{
		while (++i < obj_nb)
		{
			if (obj[i].texture->has_texture)
				mlx_destroy_image(mlx->ptr, obj[i].texture->img_ptr);
			if (obj[i].bump_map->has_texture)
				mlx_destroy_image(mlx->ptr, obj[i].bump_map->img_ptr);
		}
	}
}

void	clean_data(t_data *data)
{
	if (BONUS)
		destroy_texture(data->obj, data->obj_nb, data->mlx);
	free_list(data->obj);
	ft_free(data->scene->diffuse_light);
	clean_mlx(data->mlx);
}

void	clean_parsing_var(t_parsing *parsing_var)
{
	free_list_error(parsing_var->objs, parsing_var->mlx);
	free_str_tab(parsing_var->input_list);
	free_str_tab(parsing_var->obj_info);
	if (parsing_var->diffuse_light)
		ft_free(parsing_var->scene->diffuse_light);
	clean_mlx(parsing_var->mlx);
}
