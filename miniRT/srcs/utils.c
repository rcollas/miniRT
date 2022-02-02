# include "utils.h"

void	ft_free(void *to_free)
{
	if (to_free)
	{
		free(to_free);
		to_free = NULL;
	}
}

void	print_list(t_obj *obj)
{
	int i;

	i = 1;
	while (obj) {
		printf("-------OBJ %d--------\n", i);
		if (obj->type == SPHERE)
			printf("TYPE = SPHERE\n");
		if (obj->type == CYLINDER)
			printf("TYPE = CYLINDER\n");
		if (obj->type == PLANE)
			printf("TYPE = PLANE\n");
		printf("RGB VALUE: R = %f\n", obj->color->r);
		printf("           G = %f\n", obj->color->g);
		printf("           B = %f\n", obj->color->b);
		printf("COORDINATES: X = %f\n", obj->origin->x);
		printf("             Y = %f\n", obj->origin->y);
		printf("             Z = %f\n", obj->origin->z);
		printf("DIAMETER VALUE = %f\n", obj->diameter);
		printf("HEIGHT VALUE = %f\n\n", obj->height);
		i++;
		obj = obj->next;
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
	if ((*fd = open(file, O_DIRECTORY)) >= 0)
		return (parsing_error(IS_DIR_ERROR, file));
	if ((*fd = open(file, O_RDONLY | O_NOFOLLOW)) < 0)
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

_Bool	is_valid_extension(char *arg)
{
	char *extension;

	extension = ft_strnstr(arg, ".rt", ft_strlen(arg));
	if (!extension || ft_strcmp(extension, ".rt") == DIFFERENT)
		return (FALSE);
	return (TRUE);
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
		return (PLANE);
	return (INVALID_TYPE_ERROR);
}
