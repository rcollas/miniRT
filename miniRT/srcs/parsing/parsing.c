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

int	convert_file_to_string(int fd, char **input)
{
	int 	ret;
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
	return (SUCCESS);
}

int is_valid_type(char *type)
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
		return (PLAN);
	return (INVALID_TYPE_ERROR);
}

void	fill_structure(char **input_list)
{
	int		i;
	char	**obj_line;

	i = 0;
	while (input_list[i])
	{
		obj_line = ft_split(input_list[i], ' ');
		if (is_valid_type(obj_line[0]) == INVALID_TYPE_ERROR)
			return (ft_putstr_fd("Error\n", 2));
		i++;
	}
}

int	parsing(char **argv, int argc)
{
	int		fd;
	char	*input;
	char 	**input_list;

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
	convert_file_to_string(fd, &input);
	input_list = ft_split(input, '\n');
	fill_structure(input_list);
	return (SUCCESS);
}
