/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 15:26:48 by efrancon          #+#    #+#             */
/*   Updated: 2022/02/22 14:31:13 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_is_space(char c)
{
	if (c == '\f' || c == '\t' || c == '\n' || c == '\r' || c == '\v'
		|| c == ' ')
		return (1);
	return (0);
}

static double	convert_to_double(
	int sign, double int_part, double float_part, const char *nptr)
{
	int		is_in_fraction;
	double	divisor;

	is_in_fraction = 0;
	divisor = 1.0;
	while (*nptr)
	{
		if (ft_isdigit(*nptr) && is_in_fraction)
		{
			float_part = float_part * 10.0 + *nptr - 48;
			divisor *= 10.0;
		}
		else if (ft_isdigit(*nptr))
			int_part = int_part * 10.0 + *nptr - 48;
		else if (*nptr == '.' && is_in_fraction)
			return (sign * (int_part + float_part / divisor));
		else if (*nptr == '.')
			is_in_fraction = 1;
		else
			return (3.5e+038);
		nptr++;
	}
	return (sign * (int_part + float_part / divisor));
}

double	ft_atof(const char *nptr)
{
	double	sign;
	double	int_part;
	double	float_part;

	if (!nptr || !*nptr)
		return (0);
	sign = 1.0;
	int_part = 0;
	float_part = 0;
	while (ft_is_space(*nptr))
		nptr++;
	if (*nptr == '-')
	{
		sign *= -1.0;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	if (!*nptr)
		return (3.5e+038);
	return (convert_to_double(sign, int_part, float_part, nptr));
}
