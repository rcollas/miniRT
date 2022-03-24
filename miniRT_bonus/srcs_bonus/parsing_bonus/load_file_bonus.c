/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_file_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:45:04 by efrancon          #+#    #+#             */
/*   Updated: 2022/03/24 18:45:05 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

_Bool	file_is_complete(t_parsing *var, char *file)
{
	int	scene_objs;

	scene_objs = var->diffuse_light + var->ambient_light + var->camera;
	if (scene_objs != 3)
	{
		parsing_error(INCOMPLETE_FILE_ERROR, file);
		return (FAIL);
	}
	return (SUCCESS);
}

int	convert_file_to_string(int fd, char **input)
{
	int		ret;
	char	buff[2];

	ret = 1;
	safe_ft_strdup(input, "", fd);
	while (ret > 0)
	{
		buff[1] = 0;
		ret = safe_read(fd, buff, 1, *input);
		if (ret > 0)
			safe_ft_strjoin(input, buff, fd);
	}
	safe_close(fd);
	return (SUCCESS);
}

int	load_file(char **argv, int argc, int *fd)
{
	if (argc != 2)
	{
		parsing_error(ARG_NUMBER_ERROR, NULL);
		return (FAIL);
	}
	if (ft_open(argv[1], fd) != SUCCESS)
	{
		safe_close(*fd);
		return (FAIL);
	}
	if (is_valid_extension(argv[1]) == FALSE)
	{
		parsing_error(EXTENSION_ERROR, argv[1]);
		safe_close(*fd);
	}
	return (SUCCESS);
}
