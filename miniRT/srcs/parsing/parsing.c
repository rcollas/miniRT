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
		return (parsing_error(EXTENSION_ERROR, arg));
	return (SUCCESS);
}

int parsing(char **argv, int argc)
{
	if (argc != 2)
		return (parsing_error(ARG_NUMBER_ERROR, NULL));
	if (is_valid_extension(argv[1]) == FALSE)
		return (EXTENSION_ERROR);
	return (SUCCESS);
}