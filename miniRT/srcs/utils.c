# include "utils.h"

void	ft_free(void *to_free)
{
	if (to_free)
	{
		free(to_free);
		to_free = NULL;
	}
}

int	ft_open(char *file, int *fd)
{
	if ((*fd = open(file, O_DIRECTORY)) >= 0)
		return (parsing_error(IS_DIR_ERROR, file));
	if ((*fd = open(file, O_RDONLY)) < 0)
		return (parsing_error(FILE_ERROR, file));
	return (SUCCESS);
}

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
	char *tmp;

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
