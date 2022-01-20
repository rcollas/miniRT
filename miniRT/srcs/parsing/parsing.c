#include "miniRT.h"

_Bool	ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1 && s1[i] && s2 && s2[i] && s1[i] == s2[i])
	{
		if (s1[i + 1] == 0 && s2[i + 1] == 0)
			return (EQUAL);
		i++;
	}
	return (DIFFERENT);
}

_Bool	is_valid_extension(char *arg)
{
	char *extension;

	extension = ft_strnstr(arg, ".rt", ft_strlen(arg));
	if (!extension || ft_strcmp(extension, ".rt") == DIFFERENT)
		return (FALSE);
	return (TRUE);
}

int	ft_open(char *file, int *fd)
{
	if ((*fd = open(file, O_DIRECTORY)) >= 0)
	{
		close(*fd);
		return (parsing_error(IS_DIR_ERROR, file));
	}
	if ((*fd = open(file, O_RDONLY)) < 0)
		return (parsing_error(errno, file));
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

int	parsing(char **argv, int argc)
{
	int	fd;

	if (argc != 2)
		return (parsing_error(ARG_NUMBER_ERROR, NULL));
	if (ft_open(argv[1], &fd) != SUCCESS)
	{
		safe_close(fd);
		return (FAIL);
	}
	if (is_valid_extension(argv[1]) == FALSE)
	{
		parsing_error(EXTENSION_ERROR, argv[1]);
		safe_close(fd);
	}
	return (SUCCESS);
}
