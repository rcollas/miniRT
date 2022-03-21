/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 16:53:16 by rcollas           #+#    #+#             */
/*   Updated: 2022/02/17 17:41:19 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char			*d;
	unsigned int	i;

	if (!s)
		return (NULL);
	if (len > ft_strlen(s))
		d = ft_calloc(1, sizeof(char) * (ft_strlen(s) + 1));
	else
		d = ft_calloc(1, sizeof(char) * (len + 1));
	if (!d)
		return (NULL);
	i = 0;
	if (start < ft_strlen(s))
	{
		while (s[start + i] && i < len)
		{
			d[i] = s[start + i];
			i++;
		}
		d[i] = 0;
	}
	else
		d[0] = 0;
	return (d);
}
