/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:44:39 by efrancon          #+#    #+#             */
/*   Updated: 2022/03/25 11:27:56 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

void	ft_free(void *to_free)
{
	if (to_free)
	{
		free(to_free);
		to_free = NULL;
	}
}

void	free_list(t_obj *obj)
{
	t_obj	*tmp;

	while (obj)
	{
		tmp = obj->next;
		ft_free(obj);
		obj = tmp;
	}
}

void	free_list_error(t_obj *obj, t_mlx *mlx)
{
	t_obj	*tmp;

	while (obj)
	{
		tmp = obj->next;
		if (obj->texture->has_texture)
			mlx_destroy_image(mlx->ptr, obj->texture->img_ptr);
		if (obj->bump_map->has_texture)
			mlx_destroy_image(mlx->ptr, obj->bump_map->img_ptr);
		ft_free(obj);
		obj = tmp;
	}
}

void	free_str_tab(char **tab)
{
	int	i;

	i = -1;
	if (tab)
	{
		while (tab[++i])
			ft_free(tab[i]);
		ft_free(tab);
	}
}

void	free_tab(void **tab, int size)
{
	int	i;

	i = -1;
	while (++i < size)
		ft_free(tab[i]);
}
