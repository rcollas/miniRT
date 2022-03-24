/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 11:06:19 by efrancon          #+#    #+#             */
/*   Updated: 2022/03/24 11:06:20 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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
