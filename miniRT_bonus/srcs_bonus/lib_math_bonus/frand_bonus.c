/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frand_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:35:23 by efrancon          #+#    #+#             */
/*   Updated: 2022/03/25 11:27:56 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

unsigned int	ft_rand(void)
{
	int				fd;
	unsigned int	buff;
	unsigned int	*bit;

	fd = open("/dev/urandom", O_RDONLY);
	read(fd, &buff, sizeof(unsigned));
	bit = &buff;
	close(fd);
	return (*bit);
}

float	frand(void)
{
	float	float_rand;

	float_rand = (float)rand();
	while (float_rand > 1)
		float_rand /= 10;
	return (float_rand);
}
