/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 11:06:24 by efrancon          #+#    #+#             */
/*   Updated: 2022/03/25 14:03:20 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	ft_open(char *file, int *fd)
{
	*fd = open(file, O_DIRECTORY);
	if (*fd >= 0)
		return (parsing_error(IS_DIR_ERROR, file));
	*fd = open(file, O_RDONLY | O_NOFOLLOW);
	if (*fd < 0)
		return (parsing_error(FILE_ERROR, file));
	return (SUCCESS);
}

_Bool	is_valid_extension(char *arg)
{
	char	*extension;

	extension = ft_strnstr(arg, ".rt", ft_strlen(arg));
	if (!extension || ft_strcmp(extension, ".rt") == DIFFERENT)
		return (FALSE);
	return (TRUE);
}

int	is_valid_type(char *type)
{
	if (ft_strcmp(type, "A") == EQUAL)
		return (AMBIENT_LIGHT);
	if (ft_strcmp(type, "L") == EQUAL)
		return (DIFFUSE_LIGHT);
	if (ft_strcmp(type, "C") == EQUAL)
		return (CAMERA);
	if (ft_strcmp(type, "sp") == EQUAL)
		return (SPHERE);
	if (ft_strcmp(type, "cy") == EQUAL)
		return (CYLINDER);
	if (ft_strcmp(type, "pl") == EQUAL)
		return (PLANE);
	return (INVALID_TYPE_ERROR);
}

void	check_size_window(void)
{
	if (WIDTH < 1 || WIDTH > 1920 || HEIGHT < 1 || HEIGHT > 1080)
	{
		ft_putstr_fd("Error\nIncorrect size of the window\n", 2);
		exit(INCORRECT_SIZE_WINDOW);
	}
}
