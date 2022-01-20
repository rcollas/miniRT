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

int	convert_file_to_string(int fd, char *input)
{
	int 	ret;
	char	buff[2];

	ret = 1;
	input = ft_strdup("");
	while (ret > 0)
	{
		buff[1] = 0;
		ret = safe_read(fd, buff, 1, input);
		if (ret > 0)
			safe_ft_strjoin(&input, buff, fd);
	}
	return (0);
}

int	parsing(char **argv, int argc)
{
	int		fd;
	char	*input;

	input = NULL;
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
	convert_file_to_string(fd, input);
	return (SUCCESS);
}
