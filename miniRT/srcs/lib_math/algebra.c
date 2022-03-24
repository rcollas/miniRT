/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algebra.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 11:01:12 by efrancon          #+#    #+#             */
/*   Updated: 2022/03/24 11:01:14 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

_Bool	solve_quadratic_equation(
	double *coeff, double *roots, double *closest_hit)
{
	double	delta;

	delta = coeff[B] * coeff[B] - (4 * coeff[A] * coeff[C]);
	if (delta < 0)
		return (0);
	roots[0] = (-coeff[B] - (sqrt(delta))) / (2 * coeff[A]);
	roots[1] = (-coeff[B] + (sqrt(delta))) / (2 * coeff[A]);
	if (roots[1] < 0)
		return (FALSE);
	if (roots[0] > 0)
		*closest_hit = roots[0];
	else
		*closest_hit = roots[1];
	return (TRUE);
}
