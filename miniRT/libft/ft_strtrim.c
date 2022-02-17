/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 16:53:08 by rcollas           #+#    #+#             */
/*   Updated: 2022/02/17 14:53:06 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	is_charset(char c, char const *charset)
{
	while (*charset)
		if (c == *charset++)
			return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trim_str;
	size_t	start;
	size_t	end;
	size_t	i;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && is_charset(s1[start], set))
		start++;
	end = ft_strlen(s1);
	while (end > start && is_charset(s1[end - 1], set))
		end--;
	trim_str = (char *)ft_calloc(1, sizeof(char) * (end - start + 1));
	if (!trim_str)
		return (NULL);
	i = 0;
	while (start < end)
		trim_str[i++] = s1[start++];
	trim_str[i] = 0;
	return (trim_str);
}
