/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efrancon <efrancon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 10:52:24 by efrancon          #+#    #+#             */
/*   Updated: 2022/03/24 10:52:29 by efrancon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	safe_close(int fd)
{
	if (fd >= 0)
	{
		if (close(fd) == -1)
		{
			error(CLOSE_ERROR, ft_itoa(fd));
			exit(CLOSE_ERROR);
		}
	}
}

int	safe_read(int fd, char *buff, int buff_size, char *input)
{
	int	ret;

	ret = read(fd, buff, buff_size);
	if (ret < 0)
	{
		error(READ_ERROR, ft_itoa(fd));
		ft_free(input);
		safe_close(fd);
		exit(errno);
	}
	return (ret);
}

int	safe_ft_strjoin(char **input, char *buff, int fd)
{
	char	*tmp;

	tmp = *input;
	*input = ft_strjoin(*input, buff);
	if (!*input)
	{
		error(STRJOIN_ERROR, NULL);
		safe_close(fd);
		exit(STRJOIN_ERROR);
	}
	ft_free(tmp);
	return (SUCCESS);
}

int	safe_ft_strdup(char **dest, char *to_copy, int fd)
{
	*dest = ft_strdup(to_copy);
	if (!*dest)
	{
		error(STRDUP_ERROR, NULL);
		safe_close(fd);
		exit(STRDUP_ERROR);
	}
	return (SUCCESS);
}
