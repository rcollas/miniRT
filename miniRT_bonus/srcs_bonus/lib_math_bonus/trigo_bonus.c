/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trigo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:35:32 by efrancon          #+#    #+#             */
/*   Updated: 2022/03/24 18:35:34 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

double	convert_deg_to_rad(double angle)
{
	return (angle * M_PI / 180);
}

double	convert_rad_to_deg(double angle)
{
	return (angle * 180 / M_PI);
}
