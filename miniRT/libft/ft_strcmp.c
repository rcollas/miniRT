/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 15:27:18 by efrancon          #+#    #+#             */
/*   Updated: 2022/02/17 15:27:33 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define EQUAL 1
#define DIFFERENT 0

_Bool	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1 && s1[i] && s2 && s2[i] && s1[i] == s2[i])
	{
		if (s1[i + 1] == 0 && s2[i + 1] == 0)
			return (EQUAL);
		i++;
	}
	return (DIFFERENT);
}
