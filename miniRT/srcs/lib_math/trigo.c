/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trigo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 11:01:44 by efrancon          #+#    #+#             */
/*   Updated: 2022/03/24 11:01:45 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	convert_deg_to_rad(double angle)
{
	return (angle * M_PI / 180);
}

double	convert_rad_to_deg(double angle)
{
	return (angle * 180 / M_PI);
}
