/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colored_lights_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:34:55 by efrancon          #+#    #+#             */
/*   Updated: 2022/03/25 14:03:21 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

t_vec3	compute_light_color(t_diffuse_light *light, int light_nb)
{
	t_vec3	light_color;
	int		i;

	i = -1;
	light_color = create_vec3(0, 0, 0);
	while (++i < light_nb)
	{
		light_color = add_vec3(light_color, *light[i].color);
	}
	check_limit_color(&light_color);
	return (light_color);
}

t_vec3	compute_obj_color(t_ray *hit, t_diffuse_light *light, int light_nb)
{
	int		i;
	t_vec3	light_color;
	t_vec3	obj_color;

	i = -1;
	light_color = compute_light_color(light, light_nb);
	obj_color = mul_vec3(hit->color, light_color);
	return (hit->color);
}
