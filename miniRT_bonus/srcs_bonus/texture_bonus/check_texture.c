/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:40:56 by efrancon          #+#    #+#             */
/*   Updated: 2022/03/24 18:40:57 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

_Bool	check_file_texture(char *filename)
{
	char	*texture;

	texture = copy_end_str(filename, 5);
	if (filename[0] == '\"' && texture
		&& ft_strcmp(texture, ".xpm\""))
	{
		ft_free(texture);
		return (TRUE);
	}
	ft_free(texture);
	return (FALSE);
}

_Bool	check_file_bump_map(char *filename)
{
	char	*normal_map;

	normal_map = copy_end_str(filename, 16);
	if (filename[0] == '\"' && normal_map
		&& ft_strcmp(normal_map, "_normal_map.xpm\""))
	{
		ft_free(normal_map);
		return (TRUE);
	}
	ft_free(normal_map);
	return (FALSE);
}
