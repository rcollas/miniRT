#include "miniRT.h"

void	ft_free(void *to_free)
{
	if (to_free)
	{
		free(to_free);
		to_free = NULL;
	}
}

void	free_list(t_obj *obj)
{
	t_obj	*tmp;

	while (obj)
	{
		tmp = obj->next;
		ft_free(obj);
		obj = tmp;
	}
}

void	free_str_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		ft_free(tab[i]);
	ft_free(tab);
}

void	free_tab(void **tab, int size)
{
	int	i;

	i = -1;
	while (++i < size)
		ft_free(tab[i]);
}

void	ft_exit_parsing(int errnum, t_parsing *parsing_var)
{
	free_list(parsing_var->objs);
	free_str_tab(parsing_var->input_list);
	if (parsing_var->objs)
		free_str_tab(parsing_var->obj_info);
	exit(errnum);
}

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
	if (ft_strcmp(type, "di") == EQUAL)
		return (DISK);
	return (INVALID_TYPE_ERROR);
}
