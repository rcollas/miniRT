/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_error_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:44:28 by efrancon          #+#    #+#             */
/*   Updated: 2022/03/25 14:03:21 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

void	error_coordinates(void)
{
	ft_putstr_fd("[COORDINATES] 0.0,0.0,0.0   ", 2);
}

void	error_diameter(void)
{
	ft_putstr_fd("[DIAMETER] 0.0   ", 2);
}

void	error_height(void)
{
	ft_putstr_fd("[HEIGHT] 0.0   ", 2);
}

void	error_rgb(void)
{
	ft_putstr_fd("[RGB] 0-255,0-255,0-255   ", 2);
}

void	error_vertex(void)
{
	ft_putstr_fd("[VERTEX] 0.0,0.0,0.0   ", 2);
}
